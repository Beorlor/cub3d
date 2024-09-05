/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:22:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 10:30:51 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_ball	*set_up_ball(t_game *game, int button)
{
	if (game->ball[0].active || game->ball[1].active)
		return (NULL);
	if (button == 1)
	{
		game->ball[1].active = 0;
		return (&game->ball[0]);
	}
	else if (button == 3)
	{
		game->ball[0].active = 0;
		return (&game->ball[1]);
	}
	return (NULL);
}

void	init_ball2(t_game *game, t_ball *ball)
{
	ball->x = game->player.x;
	ball->y = game->player.y;
	ball->wx = (game->win_width / 2) - (ball->texture.width / 2);
	ball->wy = game->win_height - 180;
	ball->size = ball->texture.width;
	ball->stage = 1;
	ball->speed = 0.3;
	ball->direction_x = game->player.dir_x;
	ball->direction_y = game->player.dir_y;
	ball->active = 1;
}

void	create_ball(t_game *game, int button)
{
	t_ball	*ball;

	if (game->ball[0].active || game->ball[1].active)
		return ;
	ball = set_up_ball(game, button);
	if (ball == NULL)
		return ;
	if (!ball->active)
		init_ball2(game, ball);
}

void	move_ball_towards_center(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->center_x = game->win_width / 2.0;
	gv->center_y = game->win_height / 2.0;
	gv->dx = gv->center_x - (ball->wx + ball->size / 2.0);
	gv->dy = gv->center_y - (ball->wy + ball->size / 2.0);
	gv->distance = sqrt(gv->dx * gv->dx + gv->dy * gv->dy);
	ball->size = fmax(5, ball->size - 1);
	if (gv->distance > 100.0)
	{
		ball->wx += (gv->dx / gv->distance) * 20;
		ball->wy += (gv->dy / gv->distance) * 20;
	}
	else
	{
		ball->wx = gv->center_x - (ball->size / 2.0);
		ball->wy = gv->center_y - (ball->size / 2.0);
		ball->stage = 2;
	}
}

void	deactivate_portal(t_game *game, int portal_index)
{
	if (game->portals[portal_index].active)
	{
		game->map.map[(int)game->portals[portal_index].y][(int)game
			->portals[portal_index].x] = '1';
		game->portals[portal_index].active = 0;
		game->portals[portal_index].link = 0;
	}
}

void	unlink_portals(t_game *game)
{
	game->portals[0].link = 0;
	game->portals[1].link = 0;
}

void	handle_blue_portal(t_game *game, int map_x, int map_y, int direction)
{
	if (game->map.map[map_y][map_x] == '3')
	{
		deactivate_portal(game, 0);
		deactivate_portal(game, 1);
		unlink_portals(game);
	}
	else if (game->map.map[map_y][map_x] == '2')
	{
		game->portals[0].direction = direction;
		return ;
	}
	else if (game->map.map[map_y][map_x] == '1')
		deactivate_portal(game, 0);
	game->portals[0].active = 1;
	game->portals[0].x = map_x;
	game->portals[0].y = map_y;
	game->portals[0].direction = direction;
	game->map.map[map_y][map_x] = '2';
}

void	handle_orange_portal(t_game *game, int map_x, int map_y, int direction)
{
	if (game->map.map[map_y][map_x] == '2')
	{
		deactivate_portal(game, 0);
		deactivate_portal(game, 1);
		unlink_portals(game);
	}
	else if (game->map.map[map_y][map_x] == '3')
	{
		game->portals[1].direction = direction;
		return ;
	}
	else if (game->map.map[map_y][map_x] == '1')
		deactivate_portal(game, 1);
	game->portals[1].active = 1;
	game->portals[1].x = map_x;
	game->portals[1].y = map_y;
	game->portals[1].direction = direction;
	game->map.map[map_y][map_x] = '3';
}

void	set_portal_params(t_game *game, int portal_index, int map_x, int map_y)
{
	game->gun_vars.current_portal_index = portal_index;
	game->gun_vars.current_map_x = map_x;
	game->gun_vars.current_map_y = map_y;
}

void	place_portal(t_game *game)
{
	if (game->gun_vars.current_portal_index == 0)
		handle_blue_portal(game, game->gun_vars.current_map_x,
			game->gun_vars.current_map_y, game->gun_vars.current_direction);
	else if (game->gun_vars.current_portal_index == 1)
		handle_orange_portal(game, game->gun_vars.current_map_x,
			game->gun_vars.current_map_y, game->gun_vars.current_direction);
	if (game->portals[0].active && game->portals[1].active)
	{
		game->portals[0].link = 1;
		game->portals[1].link = 1;
	}
	else
		unlink_portals(game);
}

void	init_dda(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->delta_dist_x = fabs(1 / ball->direction_x);
	gv->delta_dist_y = fabs(1 / ball->direction_y);
	if (ball->direction_x < 0)
	{
		gv->step_x = -1;
		gv->side_dist_x = (ball->x - gv->map_x) * gv->delta_dist_x;
	}
	else
	{
		gv->step_x = 1;
		gv->side_dist_x = (gv->map_x + 1.0 - ball->x) * gv->delta_dist_x;
	}
	if (ball->direction_y < 0)
	{
		gv->step_y = -1;
		gv->side_dist_y = (ball->y - gv->map_y) * gv->delta_dist_y;
	}
	else
	{
		gv->step_y = 1;
		gv->side_dist_y = (gv->map_y + 1.0 - ball->y) * gv->delta_dist_y;
	}
}

int	perform_dda_step(t_game *game)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (gv->side_dist_x < gv->side_dist_y)
	{
		gv->side_dist_x += gv->delta_dist_x;
		gv->map_x += gv->step_x;
		gv->side = 0;
	}
	else
	{
		gv->side_dist_y += gv->delta_dist_y;
		gv->map_y += gv->step_y;
		gv->side = 1;
	}
	if (gv->map_x < 0 || gv->map_x >= game->map.width || gv->map_y < 0
		|| gv->map_y >= game->map.height
		|| game->map.map[gv->map_y][gv->map_x] == '1'
		|| game->map.map[gv->map_y][gv->map_x] == '2'
		|| game->map.map[gv->map_y][gv->map_x] == '3')
		return (1);
	if (game->map.map[gv->map_y][gv->map_x] == 'D'
		&& is_player_next_to_door(game, gv->map_x, gv->map_y))
		return (1);
	return (0);
}

void	set_direction(t_game *game)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (gv->side == 0)
	{
		if (gv->step_x > 0)
			gv->direction = EAST;
		else
			gv->direction = WEST;
	}
	else
	{
		if (gv->step_y > 0)
			gv->direction = SOUTH;
		else
			gv->direction = NORTH;
	}
}

void	set_portal_index(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (ball == &game->ball[0])
		gv->portal_index = 0;
	else
		gv->portal_index = 1;
}

void	handle_ball_collision(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (game->map.map[gv->map_y][gv->map_x] != 'D')
	{
		set_direction(game);
		set_portal_index(game, ball);
		gv->current_direction = gv->direction;
		set_portal_params(game, gv->portal_index, gv->map_x, gv->map_y);
		place_portal(game);
	}
	ball->active = 0;
}

void	move_ball_towards_wall(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->next_x = ball->x + ball->direction_x * ball->speed;
	gv->next_y = ball->y + ball->direction_y * ball->speed;
	gv->map_x = (int)gv->next_x;
	gv->map_y = (int)gv->next_y;
	init_dda(game, ball);
	while (1)
	{
		if (perform_dda_step(game))
		{
			handle_ball_collision(game, ball);
			return ;
		}
	}
	ball->x = gv->next_x;
	ball->y = gv->next_y;
	ball->size = fmax(5, ball->size - 40);
}

void	update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			if (game->ball[i].stage == 1)
				move_ball_towards_center(game, &game->ball[i]);
			else if (game->ball[i].stage == 2)
				move_ball_towards_wall(game, &game->ball[i]);
		}
		i++;
	}
}

void	load_ball_texture(t_game *game, int index, char *filename)
{
	game->ball[index].texture.img = mlx_xpm_file_to_image(game->mlx, filename,
			&game->ball[index].texture.width,
			&game->ball[index].texture.height);
	if (!game->ball[index].texture.img)
	{
		printf("Failed to load ball texture: %s\n", filename);
		free_all2(game);
	}
	game->ball[index].texture.addr = (int *)mlx_get_data_addr(game
			->ball[index].texture.img,
			&game->ball[index].texture.pixel_bits,
			&game->ball[index].texture.size_line,
			&game->ball[index].texture.endian);
}

void	load_ball_textures(t_game *game)
{
	load_ball_texture(game, 0, "src/sprites/sprites/orange_ball.xpm");
	load_ball_texture(game, 1, "src/sprites/sprites/blue_ball2.xpm");
}

void	draw_ball_pixel(t_game *game, t_texture *frame, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (gv->tex_x >= 0 && gv->tex_x < gv->tex_width && gv->tex_y >= 0
		&& gv->tex_y < gv->tex_height)
	{
		gv->color = game->ball[i].texture.addr[gv->tex_y * gv->tex_width
			+ gv->tex_x];
		gv->screen_x = gv->start_x + gv->x;
		gv->screen_y = gv->start_y + gv->y;
		if (gv->screen_x >= 0 && gv->screen_x < game->win_width
			&& gv->screen_y >= 0 && gv->screen_y < game->win_height
			&& (gv->color & 0xFFFFFF) != 0x000000)
		{
			my_mlx_pixel_put(frame, gv->screen_x, gv->screen_y, gv->color);
		}
	}
}

void	draw_ball_stage(t_game *game, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (game->ball[i].stage == 1)
	{
		gv->start_x = (game->win_width / 2) - (game->ball[i].size / 2);
		gv->start_y = game->ball[i].wy - (game->ball[i].size / 2);
	}
	else if (game->ball[i].stage == 2)
	{
		gv->start_x = (game->win_width / 2) - (game->ball[i].size / 2);
		gv->start_y = (game->win_width / 2) - (game->ball[i].size / 2);
	}
}

void	init_ball_draw(t_game *game, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->tex_width = game->ball[i].texture.width;
	gv->tex_height = game->ball[i].texture.height;
	gv->scale_x = (double)game->ball[i].size / gv->tex_width;
	gv->scale_y = (double)game->ball[i].size / gv->tex_height;
	draw_ball_stage(game, i);
}

void	draw_ball_row(t_game *game, t_texture *frame, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->x = 0;
	while (gv->x < game->ball[i].size)
	{
		gv->tex_x = (int)(gv->x / gv->scale_x);
		gv->tex_y = (int)(gv->y / gv->scale_y);
		draw_ball_pixel(game, frame, i);
		gv->x++;
	}
}

void	draw_ball(t_game *game, t_texture *frame)
{
	t_gun_vars	*gv;
	int			i;

	gv = &game->gun_vars;
	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			init_ball_draw(game, i);
			gv->y = 0;
			while (gv->y < game->ball[i].size)
			{
				draw_ball_row(game, frame, i);
				gv->y++;
			}
		}
		i++;
	}
}
