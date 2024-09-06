/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:37:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:05:42 by jeguerin         ###   ########.fr       */
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

void	calculate_gun_position(t_game *game, int *x, int *y)
{
	*x = (game->win_width - game->portal_gun.width) / 2;
	*y = game->win_height - game->portal_gun.height - 10;
	if (game->gun_shot == 1)
	{
		*y += 10;
		game->shot_frame++;
		if (game->shot_frame > 5)
		{
			game->gun_shot = 0;
			game->shot_frame = 0;
		}
	}
}

void	draw_portal_gun(t_game *game, t_texture *frame, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (!game->portal_gun.img)
	{
		printf("Portal gun image is not loaded.\n");
		return ;
	}
	while (i < game->portal_gun.height)
	{
		j = 0;
		while (j < game->portal_gun.width)
		{
			color = (int)game->portal_gun.addr[(i + 1)
				* game->portal_gun.width + j];
			if ((color & 0x00FFFFFF) != 0)
			{
				my_mlx_pixel_put(frame, x + j, y + i, color);
			}
			j++;
		}
		i++;
	}
}

void	display_portal_gun(t_game *game, t_texture *frame)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	calculate_gun_position(game, &x, &y);
	draw_portal_gun(game, frame, x, y);
}
