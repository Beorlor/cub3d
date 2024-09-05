/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_moving.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:09:52 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 07:00:44 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	moving(t_game *game, int is_moving, double move_x, double move_y)
{
	try_move(game, move_x, move_y);
	if (is_moving)
	{
		game->frame_count++;
		game->walk_offset = (int)(sin(game->frame_count * 0.1) * 10);
	}
	else
	{
		game->walk_offset = 0;
		game->frame_count = 0;
	}
}

void	if_rotate(t_game *game)
{
	double	rotation_angle;

	rotation_angle = 0.05;
	if (game->touch_state[LEFT_INDEX])
		rotate_player(game, -rotation_angle);
	if (game->touch_state[RIGHT_INDEX])
		rotate_player(game, rotation_angle);
}

void	move_north_or_south(t_game *game, double *move_x, double *move_y,
			int *is_moving)
{
	double	movement_speed;

	movement_speed = game->player.speed * 0.2;
	if (game->touch_state[W_INDEX])
	{
		(*move_x) += game->player.dir_x * movement_speed;
		(*move_y) += game->player.dir_y * movement_speed;
		(*is_moving) = 1;
	}
	if (game->touch_state[S_INDEX])
	{
		(*move_x) -= game->player.dir_x * movement_speed;
		(*move_y) -= game->player.dir_y * movement_speed;
		(*is_moving) = 1;
	}
}

void	move_east_or_west(t_game *game, double *move_x, double *move_y,
			int *is_moving)
{
	double	movement_speed;

	movement_speed = game->player.speed * 0.05;
	if (game->touch_state[A_INDEX])
	{
		(*move_x) -= game->player.plane_x * movement_speed;
		(*move_y) -= game->player.plane_y * movement_speed;
		(*is_moving) = 1;
	}
	if (game->touch_state[D_INDEX])
	{
		(*move_x) += game->player.plane_x * movement_speed;
		(*move_y) += game->player.plane_y * movement_speed;
		(*is_moving) = 1;
	}
}

// is_moving : Adjust the walk offset if the player is moving
void	is_action(t_game *game)
{
	double	move_x;
	double	move_y;
	int		is_moving;

	is_moving = 0;
	move_x = 0;
	move_y = 0;
	move_north_or_south(game, &move_x, &move_y, &is_moving);
	move_east_or_west(game, &move_x, &move_y, &is_moving);
	if_rotate(game);
	moving(game, is_moving, move_x, move_y);
}
