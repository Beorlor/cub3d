/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_ball.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:00:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:08:01 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_ball	*set_up_ball(t_game *game, int button)
{
	if (game->ball[0].active || game->ball[1].active)
		return (NULL);
	if (button == 1)
	{
		game->ball[1].active = 0;
		return (&game->ball[0]);
	}
	else if (button == 3)
	{
		game->ball[0].active = 0;
		return (&game->ball[1]);
	}
	return (NULL);
}

void	init_ball2(t_game *game, t_ball *ball)
{
	ball->x = game->player.x;
	ball->y = game->player.y;
	ball->wx = (game->win_width / 2) - (ball->texture.width / 2);
	ball->wy = game->win_height - 180;
	ball->size = ball->texture.width;
	ball->stage = 1;
	ball->speed = 0.3;
	ball->direction_x = game->player.dir_x;
	ball->direction_y = game->player.dir_y;
	ball->active = 1;
}

void	create_ball(t_game *game, int button)
{
	t_ball	*ball;

	if (game->ball[0].active || game->ball[1].active)
		return ;
	ball = set_up_ball(game, button);
	if (ball == NULL)
		return ;
	if (!ball->active)
		init_ball2(game, ball);
}

void	move_ball_towards_center(t_game *game, t_ball *ball)
{
	t_gun_vars	*gv;

	gv = &game->gun_vars;
	gv->center_x = game->win_width / 2.0;
	gv->center_y = game->win_height / 2.0;
	gv->dx = gv->center_x - (ball->wx + ball->size / 2.0);
	gv->dy = gv->center_y - (ball->wy + ball->size / 2.0);
	gv->distance = sqrt(gv->dx * gv->dx + gv->dy * gv->dy);
	ball->size = fmax(5, ball->size - 1);
	if (gv->distance > 100.0)
	{
		ball->wx += (gv->dx / gv->distance) * 20;
		ball->wy += (gv->dy / gv->distance) * 20;
	}
	else
	{
		ball->wx = gv->center_x - (ball->size / 2.0);
		ball->wy = gv->center_y - (ball->size / 2.0);
		ball->stage = 2;
	}
}

void	deactivate_portal(t_game *game, int portal_index)
{
	if (game->portals[portal_index].active)
	{
		game->map.map[(int)game->portals[portal_index].y][(int)game
			->portals[portal_index].x] = '1';
		game->portals[portal_index].active = 0;
		game->portals[portal_index].link = 0;
	}
}
