/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:05:55 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:38:56 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
