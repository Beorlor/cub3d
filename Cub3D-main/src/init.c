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
	player->rot_speed = 0.04;
}
// speed : vitesse du player en pixels.

// memset(game->texture_paths, 0, sizeof(game->texture_paths));
void	init_game(t_game *game)
{
	game->win = NULL;
	game->win_height = 800;
	game->win_width = 600;
	game->map.map = NULL;
	game->running = 1;
	memset(game->touch_state, 0, sizeof(game->touch_state));
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

void init_mini_map(t_game *game)
{
    game->mini_map.width = MINIMAP_WIDTH;
    game->mini_map.height = MINIMAP_HEIGHT;

    // Check for invalid dimensions and handle errors
    if (game->mini_map.width <= 0 || game->mini_map.height <= 0) {
        printf("Error: Invalid mini_map dimensions\n");
        free_all2(game);
        return;
    }
    game->mini_map.img = mlx_new_image(game->mlx, game->mini_map.width, game->mini_map.height);
    if (!game->mini_map.img) {
        printf("Error: Failed to create mini_map image\n");
        free_all2(game);
    }

    game->mini_map.addr = (int *)mlx_get_data_addr(game->mini_map.img, &game->mini_map.pixel_bits, &game->mini_map.size_line, &game->mini_map.endian);
    if (!game->mini_map.addr) {
        printf("Error: Failed to get mini_map data address\n");
        mlx_destroy_image(game->mlx, game->mini_map.img);
        free_all2(game);
    }
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
	init_mini_map(game);
}
