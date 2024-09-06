/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:07:49 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:08:06 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	draw_overlay_pixel(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->overlay_tex_x = (int)(rv->wall_x * (double)rv->overlay_texture->width);
	rv->overlay_tex_y = (((rv->y - rv->walk_offset) * 256 - game->win_height
				* 128 + rv->line_height * 128) * rv->overlay_texture->height)
		/ rv->line_height / 256;
	if (rv->overlay_tex_x >= 0 && rv->overlay_tex_x < rv->overlay_texture->width
		&& rv->overlay_tex_y >= 0
		&& rv->overlay_tex_y < rv->overlay_texture->height)
	{
		rv->overlay_color = rv->overlay_texture->addr[rv->overlay_tex_y
			* rv->overlay_texture->width + rv->overlay_tex_x];
		if ((rv->overlay_color & 0xFFFFFF) != 0x000000)
		{
			my_mlx_pixel_put(frame, x, rv->y, rv->overlay_color);
		}
	}
}

void	draw_wall(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->y = rv->draw_start;
	while (rv->y < rv->draw_end)
	{
		calc_tex_y(game);
		draw_wall_pixel(game, frame, x);
		if (rv->overlay_texture)
		{
			draw_overlay_pixel(game, frame, x);
		}
		rv->y++;
	}
}
