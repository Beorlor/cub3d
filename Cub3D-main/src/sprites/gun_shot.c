/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:22:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 15:41:59 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_ball	*set_up_ball(t_ball *ball, t_game *game, int button)
{
	if (button == 1)
	{
		ball = &game->ball[0];
		game->ball[1].active = 0;
	}
	else if (button == 3)
	{
		ball = &game->ball[1];
		game->ball[0].active = 0;
	}
	else
	{
		return (NULL);
	}
	return (ball);
}

// Position de départ
// ball->x = game->win_width / 2;
// ball->y = game->win_height - 250;
// ball->x = (game->win_width - game->portal_gun.width) / 2;
// ball->y = game->win_height - game->portal_gun.height - 50;
void	create_ball(t_game *game, int button)
{
	t_ball	*ball;
	double	center_x;
	double	center_y;
	double	dx;
	double	dy;
	double	distance;

	ball = NULL;
	ball = set_up_ball(ball, game, button);
	if (ball == NULL)
		return ;
	if (ball && !ball->active)
	{
		ball->x = (game->win_width / 2) - (ball->texture.width / 2);
		ball->y = (game->win_height - 180) - (ball->texture.height / 2);
		center_x = game->win_width / 2.0;
		center_y = game->win_height / 2.0;
		dx = center_x - ball->x;
		dy = center_y - ball->y;
		distance = sqrt(dx * dx + dy * dy);
		ball->direction_x = (dx / distance) * 15;
		ball->direction_y = (dy / distance) * 15;
		ball->active = 1;
	}
}

void	load_ball_textures(t_game *game)
{
	game->ball[0].texture.img = mlx_xpm_file_to_image(game->mlx,
			"src/sprites/sprites/orange_ball.xpm", &game->ball[0].texture.width,
			&game->ball[0].texture.height);
	if (!game->ball[0].texture.img)
	{
		printf("Failed to load orange ball texture\n");
		free_all2(game);
	}
	game->ball[0].texture.addr = (int *)mlx_get_data_addr(
			game->ball[0].texture.img, &game->ball[0].texture.pixel_bits,
			&game->ball[0].texture.size_line, &game->ball[0].texture.endian);
	game->ball[1].texture.img = mlx_xpm_file_to_image(game->mlx,
			"src/sprites/sprites/blue_ball2.xpm", &game->ball[1].texture.width,
			&game->ball[1].texture.height);
	if (!game->ball[1].texture.img)
	{
		printf("Failed to load blue ball texture\n");
		free_all2(game);
	}
	game->ball[1].texture.addr = (int *)mlx_get_data_addr(
			game->ball[1].texture.img, &game->ball[1].texture.pixel_bits,
			&game->ball[1].texture.size_line, &game->ball[1].texture.endian);
}

// game->ball[i].x += game->ball[i].direction_x;
// game->ball[i].y += game->ball[i].direction_y;
void	update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			move_ball_towards_center(game, &game->ball[i]);
			if (game->ball[i].x < 0 || game->ball[i].x >= game->win_width
				|| game->ball[i].y < 0 || game->ball[i].y >= game->win_height)
			{
				game->ball[i].active = 0;
			}
		}
		i++;
	}
}

void	ball_map_center(t_ball *ball, double center_x, double center_y)
{
	ball->x = center_x - (ball->texture.width / 2.0);
	ball->y = center_y - (ball->texture.height / 2.0);
	ball->direction_x = 0;
	ball->direction_y = 0;
}

// 1. Dir. vers le centre
// 2. Boule au centre
void	move_ball_towards_center(t_game *game, t_ball *ball)
{
	double	center_x;
	double	center_y;
	double	dx;
	double	dy;
	double	distance;

	center_x = game->win_width / 2.0;
	center_y = game->win_height / 2.0;
	if (ball->active)
	{
		dx = center_x - (ball->x + ball->texture.width / 2.0);
		dy = center_y - (ball->y + ball->texture.height / 2.0);
		distance = sqrt(dx * dx + dy * dy);
		if (distance > 5.0)
		{
			ball->x += (dx / distance) * 15;
			ball->y += (dy / distance) * 15;
		}
		else
			ball_map_center(ball, center_x, center_y);
	}
}

void	draw_ball(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->ball[i].texture.img, game->ball[i].x,
				game->ball[i].y);
		}
		i++;
	}
}
