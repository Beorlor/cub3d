/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:06:36 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:07:08 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
