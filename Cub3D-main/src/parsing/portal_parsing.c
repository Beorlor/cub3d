/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:33:54 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 10:38:23 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	load_portal_textures(t_game *game)
{
	game->portals[0].texture.img = mlx_xpm_file_to_image(game->mlx,
			"sprites/portal/blue_portal.xpm", &game->portals[0].texture.width,
			&game->portals[0].texture.height);
	if (!game->portals[0].texture.img)
	{
		printf("Failed to load blue portal texture\n");
		free_all2(game);
	}
	game->portals[0].texture.addr = (int *)mlx_get_data_addr(
			game->portals[0].texture.img, &game->portals[0].texture.pixel_bits,
			&game->portals[0].texture.size_line,
			&game->portals[0].texture.endian);
	game->portals[1].texture.img = mlx_xpm_file_to_image(game->mlx,
			"sprites/portal/orange_portal.xpm", &game->portals[1].texture.width,
			&game->portals[1].texture.height);
	if (!game->portals[1].texture.img)
	{
		printf("Failed to load orange portal texture\n");
		free_all2(game);
	}
	game->portals[1].texture.addr = (int *)mlx_get_data_addr(
			game->portals[1].texture.img, &game->portals[1].texture.pixel_bits,
			&game->portals[1].texture.size_line,
			&game->portals[1].texture.endian);
}
