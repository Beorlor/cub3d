/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:37:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 15:23:24 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	load_portal_gun(t_game *game)
{
	game->portal_gun.width = 64;
	game->portal_gun.height = 64;
	game->portal_gun.img = mlx_xpm_file_to_image(game->mlx,
			"src/sprites/sprites/portal_gun.xpm", &game->portal_gun.width,
			&game->portal_gun.height);
	if (!game->portal_gun.img)
	{
		printf("Failed to load portal gun texture\n");
		free_all2(game);
	}
	game->portal_gun.addr = (int *)mlx_get_data_addr(game->portal_gun.img,
			&game->portal_gun.pixel_bits, &game->portal_gun.size_line,
			&game->portal_gun.endian);
	if (!game->portal_gun.addr)
	{
		printf("Failed to load portal gun address\n");
		mlx_destroy_image(game->mlx, game->portal_gun.img);
		free_all2(game);
	}
}

void	merge_texture(t_texture *bg, t_texture *fg, t_game *game, int x, int y)
{
	int	i;
	int	j;
	int	fg_pixel;
	int	bg_pixel;
	int	transparency_color;

	(void)bg_pixel;
	(void)game;
	j = 0;
	transparency_color = 0x000000;
	while (j < fg->height)
	{
		i = 0;
		while (i < fg->width)
		{
			fg_pixel = fg->addr[j * fg->size_line / 4 + i];
			if (fg_pixel != transparency_color)
			{
				bg_pixel = bg->addr[(y + j) * bg->size_line / 4 + (x + i)];
				bg->addr[(y + j) * bg->size_line / 4 + (x + i)] = fg_pixel;
			}
			i++;
		}
		j++;
	}
}

// Créer une image de fond (background) pour l'overlay
// Copier le fond dans l'image de fond
// Fusionner les images
// Afficher l'image combinée
// Nettoyer les ressources
void	overlay_texture(t_texture *fg, t_texture *bg, t_game *game,
	int x, int y)
{
	t_texture	back;

	back.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	back.addr = (int *)mlx_get_data_addr(back.img, &back.pixel_bits,
			&back.size_line, &back.endian);
	back.width = game->win_width;
	back.height = game->win_height;
	back.pixel_bits = 32;
	back.size_line = back.width * (back.pixel_bits / 8);
	back.endian = 0;
	memcpy(back.addr, bg->addr, back.size_line * back.height);
	merge_texture(&back, fg, game, x, y);
	mlx_put_image_to_window(game->mlx, game->win, back.img, 0, 0);
	mlx_destroy_image(game->mlx, back.img);
}

// void display_portal_gun(t_game *game)
// {
//     t_texture portal_gun;
//     int x, y;

//     // Vérifie si l'image du portal gun est chargée
//     if (!game->portal_gun.img)
//     {
//         printf("Portal gun image is not loaded.\n");
//         return;
//     }

//     // Initialise la texture du portal gun
//     portal_gun.img = game->portal_gun.img;
//     portal_gun.addr = (int *)mlx_get_data_addr(portal_gun.img, 
// 		&portal_gun.pixel_bits, &portal_gun.size_line, &portal_gun.endian);
//     portal_gun.width = game->portal_gun.width;
//     portal_gun.height = game->portal_gun.height;
//     portal_gun.pixel_bits = 32;

//     // Position de l'image sur l'écran
//     x = (game->win_width - portal_gun.width) / 2;
//     y = game->win_height - portal_gun.height - 10;

//     // Vérifie si l'arme est tirée pour ajuster la position
//     if (game->gun_shot == 1)
//     {
//         y += 10;
//         game->shot_frame++;
//         if (game->shot_frame > 5)
//         {
//             game->gun_shot = 0;
//             game->shot_frame = 0;
//         }
//     }

//     // Afficher le portal gun avec transparence
//     overlay_texture(&portal_gun, &game->mini_map, game, x, y);
// }

// Recul arme
// Durée anim'
void	display_portal_gun(t_game *game)
{
	int	x;
	int	y;

	if (!game->portal_gun.img)
	{
		printf("Portal gun image is not loaded.\n");
		return ;
	}
	x = (game->win_width - game->portal_gun.width) / 2;
	y = game->win_height - game->portal_gun.height - 10;
	if (game->gun_shot == 1)
	{
		y += 10;
		game->shot_frame++;
		if (game->shot_frame > 5)
		{
			game->gun_shot = 0;
			game->shot_frame = 0;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->portal_gun.img, x, y);
}
