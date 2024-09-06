/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ball.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:53 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:03:23 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	draw_ball_pixel(t_game *game, t_texture *frame, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (gv->tex_x >= 0 && gv->tex_x < gv->tex_width && gv->tex_y >= 0
		&& gv->tex_y < gv->tex_height)
	{
		gv->color = game->ball[i].texture.addr[gv->tex_y * gv->tex_width
			+ gv->tex_x];
		gv->screen_x = gv->start_x + gv->x;
		gv->screen_y = gv->start_y + gv->y;
		if (gv->screen_x >= 0 && gv->screen_x < game->win_width
			&& gv->screen_y >= 0 && gv->screen_y < game->win_height
			&& (gv->color & 0xFFFFFF) != 0x000000)
		{
			my_mlx_pixel_put(frame, gv->screen_x, gv->screen_y, gv->color);
		}
	}
}

void	draw_ball_stage(t_game *game, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	if (game->ball[i].stage == 1)
	{
		gv->start_x = (game->win_width / 2) - (game->ball[i].size / 2);
		gv->start_y = game->ball[i].wy - (game->ball[i].size / 2);
	}
	else if (game->ball[i].stage == 2)
	{
		gv->start_x = (game->win_width / 2) - (game->ball[i].size / 2);
		gv->start_y = (game->win_width / 2) - (game->ball[i].size / 2);
	}
}

void	init_ball_draw(t_game *game, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->tex_width = game->ball[i].texture.width;
	gv->tex_height = game->ball[i].texture.height;
	gv->scale_x = (double)game->ball[i].size / gv->tex_width;
	gv->scale_y = (double)game->ball[i].size / gv->tex_height;
	draw_ball_stage(game, i);
}

void	draw_ball_row(t_game *game, t_texture *frame, int i)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->x = 0;
	while (gv->x < game->ball[i].size)
	{
		gv->tex_x = (int)(gv->x / gv->scale_x);
		gv->tex_y = (int)(gv->y / gv->scale_y);
		draw_ball_pixel(game, frame, i);
		gv->x++;
	}
}

void	draw_ball(t_game *game, t_texture *frame)
{
	t_gun_vars	*gv;
	int			i;

	gv = &game->gun_vars;
	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			init_ball_draw(game, i);
			gv->y = 0;
			while (gv->y < game->ball[i].size)
			{
				draw_ball_row(game, frame, i);
				gv->y++;
			}
		}
		i++;
	}
}
