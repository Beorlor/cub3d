/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/01 05:12:46 by jedurand         ###   ########.fr       */
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

// Function to try moving the player and handle collisions
void try_move(t_game *game, double move_x, double move_y)
{
    double new_x = game->player.x + move_x;
    double new_y = game->player.y + move_y;

    // Check collision at the player's center
    if (!is_wall(game, new_x, game->player.y)) // Move along X axis if no collision
    {
        game->player.x = new_x;
    }
    if (!is_wall(game, game->player.x, new_y)) // Move along Y axis if no collision
    {
        game->player.y = new_y;
    }
}
void is_action(t_game *game)
{
    double move_x = 0;
    double move_y = 0;

    // Reduce movement speed by using smaller increments
    double movement_speed = game->player.speed * 0.05; // Adjust this value to reduce speed

    int is_moving = 0;

    if (game->touch_state[W_INDEX]) // Move forward
    {
        move_x += game->player.dir_x * movement_speed;
        move_y += game->player.dir_y * movement_speed;
        is_moving = 1;
    }
    if (game->touch_state[S_INDEX]) // Move backward
    {
        move_x -= game->player.dir_x * movement_speed;
        move_y -= game->player.dir_y * movement_speed;
        is_moving = 1;
    }
    if (game->touch_state[A_INDEX]) // Strafe left
    {
        move_x -= game->player.plane_x * movement_speed;
        move_y -= game->player.plane_y * movement_speed;
        is_moving = 1;
    }
    if (game->touch_state[D_INDEX]) // Strafe right
    {
        move_x += game->player.plane_x * movement_speed;
        move_y += game->player.plane_y * movement_speed;
        is_moving = 1;
    }

    // Check for wall collisions
    try_move(game, move_x, move_y);

    // Adjust the walk offset if the player is moving
    if (is_moving)
    {
        game->frame_count++;
        game->walk_offset = (int)(sin(game->frame_count * 0.1) * 10); // Adjust the multiplier (10) for stronger effect
    }
    else
    {
        // Reset walk offset if the player stops moving
        game->walk_offset = 0;
        game->frame_count = 0; // Optionally reset the frame count when stopping
    }
}




// events.c
// int	manage_mouse_movement(int x, t_game *game)
// {
//     int dx;

// 	//TODO this was to stop fonction from working
//     return 0;  // Prevent using uninitialized or null values


//     // Calcul du déplacement de la souris en X
//     dx = x - game->input.last_mouse_x;
//     game->input.last_mouse_x = x;

//     // Appliquer la rotation en fonction du déplacement de la souris
//     if (dx != 0) {
//         rotate_player(game, -dx * 0.003);  // Ajuster la sensibilité de la souris si nécessaire
//     }
//     return (0);
// }

int	manage_mouse_movement(int x, int y, t_game *game)
{
	double	angle;
	int		dx;

	// Skip the event if it's triggered by the programmatic mouse move
    if (game->skip_mouse_event) {
        return (0);
    }

	(void)y;
	if (x == game->input.last_mouse_x)
		game->input.last_mouse_x = x;
	dx = x - game->input.last_mouse_x;
	game->input.last_mouse_x = x;
	angle = dx * 0.003;
	rotate_player(game, angle);
	return (0);
}

int	manage_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 3) // Clic gauche ou droit
	{
		if (game->gun_shot == 0) // Si pas de tir en cours
		{
			game->gun_shot = 1;
			game->shot_frame = 0;
		}
		create_ball(game, button);
	}
	return (0);
}
