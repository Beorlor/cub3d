/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:22:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:08:09 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

void	set_portal_params(t_game *game, int portal_index, int map_x, int map_y)
{
	game->gun_vars.current_portal_index = portal_index;
	game->gun_vars.current_map_x = map_x;
	game->gun_vars.current_map_y = map_y;
}
