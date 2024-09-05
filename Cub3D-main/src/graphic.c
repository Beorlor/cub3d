/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:18:07 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 03:21:53 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_player_next_to_door_horizontal(t_game *game, int map_x, int map_y)
{
	if (game->player.x > (map_x - 1) && game->player.x < map_x
		&& game->player.y > map_y && game->player.y < (map_y + 1))
	{
		return (1);
	}
	if (game->player.x > (map_x + 1) && game->player.x < (map_x + 2)
		&& game->player.y > map_y && game->player.y < (map_y + 1))
	{
		return (1);
	}
	return (0);
}

int	is_player_next_to_door_vertical(t_game *game, int map_x, int map_y)
{
	if (game->player.x > map_x && game->player.x < (map_x + 1)
		&& game->player.y > (map_y - 1) && game->player.y < map_y)
	{
		return (1);
	}
	if (game->player.x > map_x && game->player.x < (map_x + 1)
		&& game->player.y > (map_y + 1) && game->player.y < (map_y + 2))
	{
		return (1);
	}
	return (0);
}

int	is_player_next_to_door(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'D')
	{
		if (is_player_next_to_door_horizontal(game, map_x, map_y))
			return (1);
		if (is_player_next_to_door_vertical(game, map_x, map_y))
			return (1);
	}
	return (0);
}

void	init_render_vars(t_game *game)
{
	game->render_vars.ceiling_color = (game->ceiling.r << 16)
		| (game->ceiling.g << 8) | game->ceiling.b;
	game->render_vars.floor_color = (game->floor.r << 16)
		| (game->floor.g << 8) | game->floor.b;
	game->render_vars.mid_height = game->win_height / 2;
}

void	draw_ceiling(t_game *game, t_texture *frame)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->y = 0;
	while (rv->y < rv->mid_height + rv->walk_offset)
	{
		rv->x = 0;
		while (rv->x < game->win_width)
		{
			my_mlx_pixel_put(frame, rv->x, rv->y, rv->ceiling_color);
			rv->x++;
		}
		rv->y++;
	}
}

void	draw_floor(t_game *game, t_texture *frame)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->y = rv->mid_height + rv->walk_offset;
	while (rv->y < game->win_height)
	{
		rv->x = 0;
		while (rv->x < game->win_width)
		{
			my_mlx_pixel_put(frame, rv->x, rv->y, rv->floor_color);
			rv->x++;
		}
		rv->y++;
	}
}

void	draw_ceiling_floor(t_game *game, t_texture *frame)
{
	draw_ceiling(game, frame);
	draw_floor(game, frame);
}

void	calc_ray_dir(t_game *game, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->camera_x = (2 * x / (double)game->win_width - 1) / 2;
	rv->ray_dir_x = game->player.dir_x + game->player.plane_x * rv->camera_x;
	rv->ray_dir_y = game->player.dir_y + game->player.plane_y * rv->camera_x;
	rv->map_x = (int)game->player.x;
	rv->map_y = (int)game->player.y;
}

void	calc_step_side_dist_x(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->delta_dist_x = fabs(1 / rv->ray_dir_x);
	if (rv->ray_dir_x < 0)
	{
		rv->step_x = -1;
		rv->side_dist_x = (game->player.x - rv->map_x) * rv->delta_dist_x;
	}
	else
	{
		rv->step_x = 1;
		rv->side_dist_x = (rv->map_x + 1.0 - game->player.x) * rv->delta_dist_x;
	}
}

void	calc_step_side_dist_y(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->delta_dist_y = fabs(1 / rv->ray_dir_y);
	if (rv->ray_dir_y < 0)
	{
		rv->step_y = -1;
		rv->side_dist_y = (game->player.y - rv->map_y) * rv->delta_dist_y;
	}
	else
	{
		rv->step_y = 1;
		rv->side_dist_y = (rv->map_y + 1.0 - game->player.y) * rv->delta_dist_y;
	}
}

void	calc_step_side_dist(t_game *game)
{
	calc_step_side_dist_x(game);
	calc_step_side_dist_y(game);
}

void	perform_dda_step(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	if (rv->side_dist_x < rv->side_dist_y)
	{
		rv->side_dist_x += rv->delta_dist_x;
		rv->map_x += rv->step_x;
		rv->side = 0;
	}
	else
	{
		rv->side_dist_y += rv->delta_dist_y;
		rv->map_y += rv->step_y;
		rv->side = 1;
	}
}

void	perform_dda(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->hit = 0;
	while (rv->hit == 0)
	{
		perform_dda_step(game);
		if (game->map.map[rv->map_y][rv->map_x] == '1'
			|| game->map.map[rv->map_y][rv->map_x] == '2'
			|| game->map.map[rv->map_y][rv->map_x] == '3'
			|| is_player_next_to_door(game, rv->map_x, rv->map_y))
		{
			rv->hit = 1;
		}
	}
}

void	calc_wall_dist(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	if (rv->side == 0)
		rv->perp_wall_dist = (rv->map_x - game->player.x + (1 - rv->step_x) / 2)
			/ rv->ray_dir_x;
	else
		rv->perp_wall_dist = (rv->map_y - game->player.y + (1 - rv->step_y) / 2)
			/ rv->ray_dir_y;
}

void	calc_wall_height(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->line_height = (int)(game->win_height / rv->perp_wall_dist);
	rv->draw_start = -rv->line_height / 2 + game->win_height / 2
		+ rv->walk_offset;
	if (rv->draw_start < 0)
		rv->draw_start = 0;
	rv->draw_end = rv->line_height / 2 + game->win_height / 2 + rv->walk_offset;
	if (rv->draw_end >= game->win_height)
		rv->draw_end = game->win_height - 1;
}

void	calc_wall_dist_height(t_game *game)
{
	calc_wall_dist(game);
	calc_wall_height(game);
}

void	determine_wall_texture(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	if (rv->side == 0)
	{
		if (rv->step_x > 0)
			rv->texture = &game->textures[EAST];
		else
			rv->texture = &game->textures[WEST];
	}
	else
	{
		if (rv->step_y > 0)
			rv->texture = &game->textures[SOUTH];
		else
			rv->texture = &game->textures[NORTH];
	}
}

void	determine_overlay_texture(t_game *game)
{
	t_render_vars	*rv;
	int				portal_index;

	rv = &game->render_vars;
	rv->overlay_texture = NULL;
	if (game->map.map[rv->map_y][rv->map_x] == '2'
		|| game->map.map[rv->map_y][rv->map_x] == '3')
	{
		if (game->map.map[rv->map_y][rv->map_x] == '2')
			portal_index = 0;
		else
			portal_index = 1;
		if ((rv->side == 0 && game->portals[portal_index].direction == EAST
				&& rv->step_x > 0)
			|| (rv->side == 0 && game->portals[portal_index].direction == WEST
				&& rv->step_x <= 0)
			|| (rv->side == 1 && game->portals[portal_index].direction == SOUTH
				&& rv->step_y > 0)
			|| (rv->side == 1 && game->portals[portal_index].direction == NORTH
				&& rv->step_y <= 0))
		{
			rv->overlay_texture = &game->portals[portal_index].texture;
		}
	}
}

void	calc_wall_x(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	if (rv->side == 0)
		rv->wall_x = game->player.y + rv->perp_wall_dist * rv->ray_dir_y;
	else
		rv->wall_x = game->player.x + rv->perp_wall_dist * rv->ray_dir_x;
	rv->wall_x -= floor(rv->wall_x);
}

void	calc_tex_x(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->tex_x = (int)(rv->wall_x * (double)rv->texture->width);
	if (rv->tex_x < 0)
		rv->tex_x = 0;
	if (rv->tex_x >= rv->texture->width)
		rv->tex_x = rv->texture->width - 1;
	if (rv->side == 0 && rv->step_x < 0)
		rv->tex_x = rv->texture->width - rv->tex_x - 1;
	if (rv->side == 1 && rv->step_y > 0)
		rv->tex_x = rv->texture->width - rv->tex_x - 1;
}

void	determine_texture(t_game *game)
{
	determine_wall_texture(game);
	determine_overlay_texture(game);
	calc_wall_x(game);
	calc_tex_x(game);
}

void	calc_tex_y(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->tex_y = (((rv->y - rv->walk_offset) * 256 - game->win_height * 128
				+ rv->line_height * 128) * rv->texture->height)
		/ rv->line_height / 256;
	if (rv->tex_y < 0)
		rv->tex_y = 0;
	if (rv->tex_y >= rv->texture->height)
		rv->tex_y = rv->texture->height - 1;
}

void	draw_wall_pixel(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->color = rv->texture->addr[rv->tex_y * rv->texture->width + rv->tex_x];
	if (rv->side == 1)
		rv->color = (rv->color >> 1) & 0x7F7F7F;
	my_mlx_pixel_put(frame, x, rv->y, rv->color);
}

void	draw_overlay_pixel(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->overlay_tex_x = (int)(rv->wall_x * (double)rv->overlay_texture->width);
	rv->overlay_tex_y = (((rv->y - rv->walk_offset) * 256 - game->win_height
				* 128 + rv->line_height * 128) * rv->overlay_texture->height)
		/ rv->line_height / 256;
	if (rv->overlay_tex_x >= 0 && rv->overlay_tex_x < rv->overlay_texture->width
		&& rv->overlay_tex_y >= 0
		&& rv->overlay_tex_y < rv->overlay_texture->height)
	{
		rv->overlay_color = rv->overlay_texture->addr[rv->overlay_tex_y
			* rv->overlay_texture->width + rv->overlay_tex_x];
		if ((rv->overlay_color & 0xFFFFFF) != 0x000000)
		{
			my_mlx_pixel_put(frame, x, rv->y, rv->overlay_color);
		}
	}
}

void	draw_wall(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->y = rv->draw_start;
	while (rv->y < rv->draw_end)
	{
		calc_tex_y(game);
		draw_wall_pixel(game, frame, x);
		if (rv->overlay_texture)
		{
			draw_overlay_pixel(game, frame, x);
		}
		rv->y++;
	}
}

void	render_scene(t_game *game, t_texture *frame)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	init_render_vars(game);
	draw_ceiling_floor(game, frame);
	rv->x = 0;
	while (rv->x < game->win_width)
	{
		calc_ray_dir(game, rv->x);
		calc_step_side_dist(game);
		perform_dda(game);
		calc_wall_dist_height(game);
		determine_texture(game);
		draw_wall(game, frame, rv->x);
		rv->x++;
	}
}
