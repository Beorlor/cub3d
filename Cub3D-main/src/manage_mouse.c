/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:51:31 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 20:27:06 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// int	manage_mouse_movement(int x, int y, t_game *game)
// {
// 	double	angle;
// 	int		dx;

// 	if (game->skip_mouse_event)
// 		return (0);
// 	(void)y;
// 	if (x == game->input.last_mouse_x)
// 		game->input.last_mouse_x = x;
// 	dx = x - game->input.last_mouse_x;
// 	game->input.last_mouse_x = x;
// 	angle = dx * 0.003;
// 	rotate_player(game, angle);
// 	return (0);
// }

int	manage_mouse_movement(int x, int y, t_game *game)
{
	double	angle;
	int		dx;
	int		center_x;
	int		center_y;

	(void)y;
	(void)center_y;
	if (game->skip_mouse_event)
		return (0);
	center_x = game->win_width / 2;
	center_y = game->win_height / 2;
	dx = x - center_x;
	angle = dx * 0.003;
	rotate_player(game, angle);
	// game->skip_mouse_event = 1;
	// mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	// game->skip_mouse_event = 0;
	return (0);
}


int	manage_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 3)
	{
		if (game->gun_shot == 0)
		{
			game->gun_shot = 1;
			game->shot_frame = 0;
		}
		create_ball(game, button);
	}
	return (0);
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
//         rotate_player(game, -dx * 0.003);
//     }
//     return (0);
// }
