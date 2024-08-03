/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:57:03 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:57:03 by marvin           ###   ########.fr       */
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
	player->rot_speed = 0.03;
}
// speed : vitesse du player en pixels.

// memset(game->texture_paths, 0, sizeof(game->texture_paths));
void	init_game(t_game *game)
{
	game->win = NULL;
	game->win_height = 0;
	game->win_width = 0;
	game->map.map = NULL;
	game->running = 1;
}
// int	i;

	// i = 0;
	// while (i < 4)
	// {
	// 	game->texture_paths[i] = NULL;
	// 	i++;
	// }

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
}

void	init_cub(t_game *game)
{
	init_game(game);
	init_player(&game->player);
	init_color(&game->floor);
	init_color(&game->ceiling);
	init_texture(game->textures);
	init_map(&game->map);
	init_input(&game->input);
}
