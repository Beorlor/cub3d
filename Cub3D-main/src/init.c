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
void init_portals(t_game *game)
{
    for (int i = 0; i < 2; i++)
    {
        game->portals[i].active = 0;
        game->portals[i].x = 0;
        game->portals[i].y = 0;
        game->portals[i].texture.img = NULL;
        game->portals[i].texture.addr = NULL;
    }
}

// memset(game->texture_paths, 0, sizeof(game->texture_paths));
void	init_game(t_game *game)
{
	game->win = NULL;
	game->win_height = 800;
	game->win_width = 800;
	game->map.map = NULL;
	game->running = 1;
	game->orientation = 0;
	memset(game->touch_state, 0, sizeof(game->touch_state));
	game->portal_gun.img = NULL;
    game->portal_gun.addr = NULL;
    game->portal_gun.pixel_bits = 0;
    game->portal_gun.size_line = 0;
    game->portal_gun.endian = 0;
	game->gun_shot = 0;
	game->shot_frame = 0;
	init_textures(game);
	init_ball(game);
	load_portal_gun(game);
	init_portals(game);
	game->frame_count = 0;
	game->walk_offset = 0;
	game->skip_mouse_event = 0;
}

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

void	init_ball(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		game->ball[i].texture.img = NULL;
		game->ball[i].texture.addr = NULL;
		game->ball[i].texture.pixel_bits = 0;
		game->ball[i].texture.size_line = 0;
		game->ball[i].texture.endian = 0;
		game->ball[i].texture.width = 64;
		game->ball[i].texture.height = 64;
		game->ball[i].x = 0;
		game->ball[i].y = 0;
		game->ball[i].direction_x = 0;
		game->ball[i].direction_y = 0;
		game->ball[i].active = 0;
		i++;
	}
	load_ball_textures(game);

}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].addr = NULL;
		game->textures[i].img = NULL;
		game->textures[i].pixel_bits = 0;
		game->textures[i].size_line = 0;
		game->textures[i].endian = 0;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		i++;
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
