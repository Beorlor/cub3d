/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/25 20:01:45 by jedurand         ###   ########.fr       */
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

// events.c
void	is_action(t_game *game)
{
    if (game->touch_state[W_INDEX])
        update_position(game, game->player.dir_x, game->player.dir_y);  // Avancer dans la direction du regard
    if (game->touch_state[S_INDEX])
        update_position(game, -game->player.dir_x, -game->player.dir_y);  // Reculer
    if (game->touch_state[A_INDEX])
        update_position(game, -game->player.plane_x, -game->player.plane_y);  // Aller à gauche
    if (game->touch_state[D_INDEX])
        update_position(game, game->player.plane_x, game->player.plane_y);  // Aller à droite
}


// events.c
int	manage_mouse_movement(int x, t_game *game)
{
    int dx;

    // Calcul du déplacement de la souris en X
    dx = x - game->input.last_mouse_x;
    game->input.last_mouse_x = x;

    // Appliquer la rotation en fonction du déplacement de la souris
    if (dx != 0) {
        rotate_player(game, -dx * 0.003);  // Ajuster la sensibilité de la souris si nécessaire
    }
    return (0);
}


