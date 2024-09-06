/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:05:54 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:06:08 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

void	perform_dda_step2(t_game *game)
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
		perform_dda_step2(game);
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
