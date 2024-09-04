/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:57:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 10:58:13 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->speed = 0.05;
	player->rot_speed = 0.04;
}

void	init_portals(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		game->portals[i].active = 0;
		game->portals[i].x = 0;
		game->portals[i].y = 0;
		game->portals[i].texture.img = NULL;
		game->portals[i].texture.addr = NULL;
		game->portals[i].direction = 0;
		game->portals[i].link = 0;
		i++;
	}
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
}
