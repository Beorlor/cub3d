/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 16:10:23 by jeguerin         ###   ########.fr       */
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

// Function to try moving the player and handle collisions
// Move along X axis if no collision
// Move along Y axis if no collision
void	try_move(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (!is_wall(game, new_x, game->player.y))
	{
		game->player.x = new_x;
	}
	if (!is_wall(game, game->player.x, new_y))
	{
		game->player.y = new_y;
	}
}
