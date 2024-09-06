/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:09:50 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:11:51 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	init_render_vars(t_game *game)
{
	game->render_vars.ceiling_color = (game->ceiling.r << 16)
		| (game->ceiling.g << 8) | game->ceiling.b;
	game->render_vars.floor_color = (game->floor.r << 16)
		| (game->floor.g << 8) | game->floor.b;
	game->render_vars.mid_height = game->win_height / 2;
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
