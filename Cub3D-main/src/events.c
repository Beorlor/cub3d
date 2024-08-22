/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/12 19:03:01 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	manage_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_all2(game);
	else if (keycode == KEY_W)
		game->touch_state[W_INDEX] = 1;
	else if (keycode == KEY_A)
		game->touch_state[A_INDEX] = 1;
	else if (keycode == KEY_S)
		game->touch_state[S_INDEX] = 1;
	else if (keycode == KEY_D)
		game->touch_state[D_INDEX] = 1;
	else if (keycode == KEY_LEFT)
		game->touch_state[LEFT_INDEX] = 1;
	else if (keycode == KEY_RIGHT)
		game->touch_state[RIGHT_INDEX] = 1;
	return (0);
}

int	manage_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->touch_state[W_INDEX] = 0;
	else if (keycode == KEY_A)
		game->touch_state[A_INDEX] = 0;
	else if (keycode == KEY_S)
		game->touch_state[S_INDEX] = 0;
	else if (keycode == KEY_D)
		game->touch_state[D_INDEX] = 0;
	else if (keycode == KEY_LEFT)
		game->touch_state[LEFT_INDEX] = 0;
	else if (keycode == KEY_RIGHT)
		game->touch_state[RIGHT_INDEX] = 0;
	return (0);
}

// void	is_action(t_game *game)
// {
// 	if (game->touch_state[W_INDEX])
// 		update_position(game, game->player.dir_x * game->player.speed,
// 			game->player.dir_y * game->player.speed);
// 	else if (game->touch_state[A_INDEX])
// 		update_position(game, game->player.dir_y * game->player.speed,
// 			-game->player.dir_x * game->player.speed);
// 	else if (game->touch_state[S_INDEX])
// 		update_position(game, -game->player.dir_x * game->player.speed,
// 			-game->player.dir_y * game->player.speed);
// 	else if (game->touch_state[D_INDEX])
// 		update_position(game, -game->player.dir_y * game->player.speed,
// 			game->player.dir_x * game->player.speed);
// 	else if (game->touch_state[LEFT_INDEX])
// 		rotate_player(game, -1);
// 	else if (game->touch_state[RIGHT_INDEX])
// 		rotate_player(game, 1);
// }

void	is_action(t_game *game)
{
	if (game->touch_state[W_INDEX])
		update_position(game, game->player.dir_x, game->player.dir_y);
	else if (game->touch_state[A_INDEX])
		update_position(game, -game->player.plane_x, -game->player.plane_y);
	else if (game->touch_state[S_INDEX])
		update_position(game, -game->player.dir_x, -game->player.dir_y);
	else if (game->touch_state[D_INDEX])
		update_position(game, game->player.plane_x, game->player.plane_y);
	else if (game->touch_state[LEFT_INDEX])
		rotate_player(game, 1);
	else if (game->touch_state[RIGHT_INDEX])
		rotate_player(game, -1);
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
