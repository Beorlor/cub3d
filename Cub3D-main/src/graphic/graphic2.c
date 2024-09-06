/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:05:20 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:07:01 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
