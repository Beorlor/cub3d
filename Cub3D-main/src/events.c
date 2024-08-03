/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 18:16:36 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// Maybe put a condition to be sure that we are in the tab. 
// int	manage_keypress(int keycode, t_game *game)
// {
// 	if (keycode >= 0 && keycode < 256)
// 		game->input.keys[keycode] = 1;
// 	printf("Key pressed: %d\n", keycode);
// 	return (0);
// }

// if (keycode == KEY_UP)
	// 	move_forward(game);
	// else if (keycode == KEY_DOWN)
	// 	move_backward(game);
int	manage_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_all2(game);
	else if (keycode == KEY_W)
	{
		printf("LOL\n");
		update_position(game, game->player.dir_x * game->player.speed,
			game->player.dir_y * game->player.speed);
	}
	else if (keycode == KEY_A)
		update_position(game, game->player.dir_y * game->player.speed,
			-game->player.dir_x * game->player.speed);
	else if (keycode == KEY_S)
		update_position(game, -game->player.dir_x * game->player.speed,
			-game->player.dir_y * game->player.speed);
	else if (keycode == KEY_D)
		update_position(game, -game->player.dir_y * game->player.speed,
			game->player.dir_x * game->player.speed);
	else if (keycode == KEY_LEFT)
		rotate_player(game, game->player.rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, -game->player.rot_speed);
	printf("Key pressed: %d\n", keycode);
	return (0);
}

// if (keycode >= 0 && keycode < 256)
	// 	game->input.keys[keycode] = 0;
	// printf("Key released: %d\n", keycode);
int	manage_keyrelease(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

int	manage_mouse_movement(int x, int y, t_game *game)
{
	double	angle;
	int		dx;

	(void)y;
	if (x == game->input.last_mouse_x)
		game->input.last_mouse_x = x;
	dx = x - game->input.last_mouse_x;
	game->input.last_mouse_x = x;
	angle = dx * 0.003;
	printf("Before rotation:\n");
	printf("Mouse dx = %d, Angle = %f\n", dx, angle);
	printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x, game->player.dir_y);
	printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x, game->player.plane_y);
	rotate_player(game, angle);
	printf("After rotation:\n");
	printf("Mouse dx = %d, Angle = %f\n", dx, angle);
	printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x, game->player.dir_y);
	printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x, game->player.plane_y);
	return (0);
}

// void	render_frame(t_game *game)
// {

// }
