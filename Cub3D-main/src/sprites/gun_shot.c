/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:22:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/01 05:55:06 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_ball	*set_up_ball(t_game *game, int button)
{
	t_ball	*ball;

	if (game->ball[0].active || game->ball[1].active)
		return (NULL);  // Prevent shooting if a ball is already active

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

// Initialize the ball and set its initial positions
void	create_ball(t_game *game, int button)
{
	t_ball	*ball;

	// Prevent shooting if a ball is already active
	if (game->ball[0].active || game->ball[1].active)
		return;

	ball = set_up_ball(game, button);
	if (ball == NULL)
		return;

	if (!ball->active)
	{
		// Initialize ball's real position (map coordinates)
		ball->x = game->player.x;
		ball->y = game->player.y;

		// Initialize ball's window position (screen coordinates)
		ball->wx = (game->win_width / 2) - (ball->texture.width / 2);
		ball->wy = game->win_height - 180;

		ball->size = ball->texture.width;
		ball->stage = 1; // Start at stage 1
		ball->speed = 0.5; // Set the speed for the ball (slow)

		// Set the direction based on the player's direction
		ball->direction_x = game->player.dir_x * ball->speed;
		ball->direction_y = game->player.dir_y * ball->speed;

		ball->active = 1;
	}
}

// Move the ball towards the center of the screen (first stage of the animation)
void	move_ball_towards_center(t_game *game, t_ball *ball)
{
	double	center_x;
	double	center_y;
	double	dx;
	double	dy;
	double	distance;

	center_x = game->win_width / 2.0;
	center_y = game->win_height / 2.0;
	dx = center_x - (ball->wx + ball->size / 2.0);
	dy = center_y - (ball->wy + ball->size / 2.0);
	distance = sqrt(dx * dx + dy * dy);

	if (distance > 5.0)
	{
		ball->wx += (dx / distance) * ball->speed;
		ball->wy += (dy / distance) * ball->speed;
	}
	else
	{
		ball->wx = center_x - (ball->size / 2.0);
		ball->wy = center_y - (ball->size / 2.0);
		ball->stage = 2; // Move to stage 2
	}
}

// Move the ball towards the wall and shrink it (second stage of the animation)
void	move_ball_towards_wall(t_game *game, t_ball *ball)
{
	int		map_x;
	int		map_y;

	// Update the ball's position in the game world
	ball->x += ball->direction_x;
	ball->y += ball->direction_y;

	// Convert the real position to screen coordinates
	ball->wx += ball->direction_x * T_SIZE;
	ball->wy += ball->direction_y * T_SIZE;

	// Check if the ball hits a wall
	map_x = (int)(ball->x);
	map_y = (int)(ball->y);
	if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height || game->map.map[map_y][map_x] == '1')
	{
		printf("Ball disappeared at size: %d\n", ball->size);
		ball->active = 0;
		return;
	}

	// Shrink the ball as it moves towards the wall
	ball->size = fmax(5, ball->size - 1);

	if (ball->size <= 5)
	{
		printf("Ball disappeared at size: %d\n", ball->size);
		ball->active = 0;
	}
}

// Update the state of the balls
void	update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			if (game->ball[i].stage == 1)
				move_ball_towards_center(game, &game->ball[i]);
			else if (game->ball[i].stage == 2)
				move_ball_towards_wall(game, &game->ball[i]);

			// Print ball position and size
			printf("Ball Position: x=%.2f, y=%.2f, wx=%.2f, wy=%.2f, size=%d\n",
				game->ball[i].x, game->ball[i].y, game->ball[i].wx, game->ball[i].wy, game->ball[i].size);
		}
		i++;
	}
}

// Load the textures for the balls
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

// Draw the ball on the screen
void	draw_ball(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->ball[i].texture.img, game->ball[i].wx - (game->ball[i].size / 2.0),
				game->ball[i].wy - (game->ball[i].size / 2.0));
		}
		i++;
	}
}
