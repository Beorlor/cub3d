/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/26 00:11:17 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	check_map_path(double x, double y, t_game *game)
// {
// 	if (game->map.map[y][x] != '1')
// 	{
// 		mlx_put_image_to_window(game->mlx, game->win, game->floor.b,
//			game->player.x, game->player.y);
// 		game->player.x = x;
// 		game->player.y = y;
// 		mlx_put_image_to_window(game->mlx, game->win, game->ceiling.r,
//			game->player.x, game->player.y);
// 	}
// }

// printf("Map-x : %d\n", map_x);
	// printf("Width : %d\n", game->map.width);
	// printf("Height : %d\n", game->map.height);
int	is_outside(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (1);
	if (game->map.map[map_y][map_x] == ' '
		|| game->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

// if pas de collision pour le nouveau x
		// on attribue la nouvelle valeur a x
	// If pas de collision pour le nouveau y
		// on attribue la nouvelle valeur a y

// void	update_position(t_game *game, double move_x, double move_y)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->player.x + move_x;
// 	new_y = game->player.y + move_y;
// 	if (!is_outside(game, new_x, new_y))
// 	{
// 		game->player.x = new_x;
// 		game->player.y = new_y;
// 	}
// 	else
// 	{
// 		if (!is_outside(game, new_x, game->player.y))
// 			game->player.x = new_x;
// 		if (!is_outside(game, game->player.x, new_y))
// 			game->player.y = new_y;
// 	}
// 	printf("New position x : %f\n", game->player.x);
// 	printf("New position y : %f\n", game->player.y);
// }

void	update_position(t_game *game, double move_x, double move_y)
{
    double	new_x;
    double	new_y;

    // Calcul des nouvelles coordonnées en fonction de la direction du joueur
    new_x = game->player.x + move_x * game->player.speed;
    new_y = game->player.y + move_y * game->player.speed;

    // Vérification des collisions avant d'assigner les nouvelles coordonnées
    if (!is_wall(game, new_x, game->player.y)) {
        game->player.x = new_x; // Mise à jour de la position en X si pas de collision
    }

    if (!is_wall(game, game->player.x, new_y)) {
        game->player.y = new_y; // Mise à jour de la position en Y si pas de collision
    }
}


// void	rotate_player(t_game *game, double angle)
// {
// 	double	old_dir_x;
// 	double	old_dir_y;
// 	double	old_plane_x;
// 	double	old_plane_y;

// 	old_dir_x = game->player.dir_x;
// 	old_dir_y = game->player.dir_y;
// 	old_plane_x = game->player.plane_x;
// 	old_plane_y = game->player.plane_y;
// 	// printf("angle : %f\n", angle);
// 	angle *= game->player.rot_speed;
// 	printf("After angle : %f\n", angle);
// 	game->player.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
// 	game->player.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
// 	game->player.plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
// 	game->player.plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);
// 	// printf("dir_x : %f\n", game->player.dir_x);
// 	// printf("dir_y : %f\n", game->player.dir_y);
// 	// printf("plane_x : %f\n", game->player.plane_x);
// 	// printf("plane_y : %f\n", game->player.plane_y);
// }

void rotate_player(t_game *game, double angle)
{
    // Save old direction values
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;

    // Apply rotation using trigonometric functions
    game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);

    game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}



// void	rotate_player(t_game *game, int direction)
// {
//     double old_dir_x;
//     double old_plane_x;
//     double rotation_speed;

//     old_dir_x = game->player.dir_x;
//     old_plane_x = game->player.plane_x;
//     rotation_speed = direction * game->player.rot_speed;
//     game->player.dir_x = game->player.dir_x * cos(rotation_speed) - game->player.dir_y * sin(rotation_speed);
//     game->player.dir_y = old_dir_x * sin(rotation_speed) + game->player.dir_y * cos(rotation_speed);
//     game->player.plane_x = game->player.plane_x * cos(rotation_speed) - game->player.plane_y * sin(rotation_speed);
//     game->player.plane_y = old_plane_x * sin(rotation_speed) + game->player.plane_y * cos(rotation_speed);
// }

// void    display_mini_map(t_game *game, t_texture *frame)
// {
//     t_texture mini_map;

//     (void)frame;
//     mini_map.width = M_SIZE * T_SIZE;
//     mini_map.height = M_SIZE * T_SIZE;
//     mini_map.img = mlx_new_image(game->mlx, mini_map.width, mini_map.height);
//     mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.pixel_bits, &mini_map.size_line, &mini_map.endian);
//     draw_mini_map(game, &mini_map);
//     draw_player(game, &mini_map);
//     mlx_put_image_to_window(game->mlx, game->win, mini_map.img, 10, 10); // Positionne la mini-map
//     mlx_destroy_image(game->mlx, mini_map.img);
// }

int display_each_frame(t_game *game)
{
    // Clear the frame
    t_texture frame;
    frame.width = game->win_width;
    frame.height = game->win_height;
    frame.img = mlx_new_image(game->mlx, frame.width, frame.height);
    frame.addr = (int *)mlx_get_data_addr(frame.img, &frame.pixel_bits, &frame.size_line, &frame.endian);

    // Draw the minimap and player on the frame
    draw_mini_map(game);

    // Render the minimap to the window, with a larger size
    mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 10, 10); // Position on the window

    // Clean up the frame resources
    mlx_destroy_image(game->mlx, frame.img);

    // Handle player movement and actions
    is_action(game);

    return 0;
}


