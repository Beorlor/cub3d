/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:36:20 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 16:50:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_color(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	init_texture(t_texture *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->pixel_bits = 0;
	texture->size_line = 0;
	texture->endian = 0;
	texture->width = 0;
	texture->height = 0;
}

// int	i;

	// i = 0;
	// while (i < 256)
	// {
	// 	input->keys[i] = 0;
	// 	i++;
	// }
void	init_input(t_input *input)
{
	input->mouse_x = 0;
	input->mouse_y = 0;
	input->last_mouse_x = -1;
	input->last_mouse_y = 0;
	input->mouse_left_pressed = 0;
}

void	init_ceiling_colors(t_game *game, int r, int g, int b)
{
	game->ceiling.r = r;
	game->ceiling.g = g;
	game->ceiling.b = b;
}

void	init_floor_colors(t_game *game, int r, int g, int b)
{
	game->floor.r = r;
	game->floor.g = g;
	game->floor.b = b;
}
