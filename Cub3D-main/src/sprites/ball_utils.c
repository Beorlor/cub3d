/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:03:54 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:04:25 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
