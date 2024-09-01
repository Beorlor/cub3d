/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:37:09 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 15:33:28 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	load_north(t_game *game)
{
	game->textures[0].width = 64;
	game->textures[0].height = 64;
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx,
			game->texture_paths[NORTH], &game->textures[0].width,
			&game->textures[0].height);
	game->textures[0].addr = (int *)mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].pixel_bits, &game->textures[0].size_line,
			&game->textures[0].endian);
}

void	load_east(t_game *game)
{
	game->textures[1].width = 64;
	game->textures[1].height = 64;
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx,
			game->texture_paths[EAST], &game->textures[1].width,
			&game->textures[1].height);
	game->textures[1].addr = (int *)mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].pixel_bits, &game->textures[1].size_line,
			&game->textures[1].endian);
}

void	load_west(t_game *game)
{
	game->textures[2].width = 64;
	game->textures[2].height = 64;
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx,
			game->texture_paths[WEST], &game->textures[2].width,
			&game->textures[2].height);
	game->textures[2].addr = (int *)mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].pixel_bits, &game->textures[2].size_line,
			&game->textures[2].endian);
}

void	load_south(t_game *game)
{
	game->textures[3].width = 64;
	game->textures[3].height = 64;
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx,
			game->texture_paths[SOUTH], &game->textures[3].width,
			&game->textures[3].height);
	game->textures[3].addr = (int *)mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].pixel_bits, &game->textures[3].size_line,
			&game->textures[3].endian);
}

void	load_textures(t_game *game)
{
	if (game->orientation == 1)
		load_north(game);
	else if (game->orientation == 2)
		load_east(game);
	else if (game->orientation == 3)
		load_west(game);
	else if (game->orientation == 4)
		load_south(game);
}
