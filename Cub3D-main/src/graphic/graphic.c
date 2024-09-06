/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:18:07 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 03:21:53 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	calc_tex_x(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->tex_x = (int)(rv->wall_x * (double)rv->texture->width);
	if (rv->tex_x < 0)
		rv->tex_x = 0;
	if (rv->tex_x >= rv->texture->width)
		rv->tex_x = rv->texture->width - 1;
	if (rv->side == 0 && rv->step_x < 0)
		rv->tex_x = rv->texture->width - rv->tex_x - 1;
	if (rv->side == 1 && rv->step_y > 0)
		rv->tex_x = rv->texture->width - rv->tex_x - 1;
}

void	determine_texture(t_game *game)
{
	determine_wall_texture(game);
	determine_overlay_texture(game);
	calc_wall_x(game);
	calc_tex_x(game);
}

void	calc_tex_y(t_game *game)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->tex_y = (((rv->y - rv->walk_offset) * 256 - game->win_height * 128
				+ rv->line_height * 128) * rv->texture->height)
		/ rv->line_height / 256;
	if (rv->tex_y < 0)
		rv->tex_y = 0;
	if (rv->tex_y >= rv->texture->height)
		rv->tex_y = rv->texture->height - 1;
}

void	draw_wall_pixel(t_game *game, t_texture *frame, int x)
{
	t_render_vars	*rv;

	rv = &game->render_vars;
	rv->color = rv->texture->addr[rv->tex_y * rv->texture->width + rv->tex_x];
	if (rv->side == 1)
		rv->color = (rv->color >> 1) & 0x7F7F7F;
	my_mlx_pixel_put(frame, x, rv->y, rv->color);
}
