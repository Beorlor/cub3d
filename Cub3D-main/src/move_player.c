/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 01:27:01 by jedurand         ###   ########.fr       */
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


void update_position(t_game *game, double move_x, double move_y)
{
    double new_x = game->player.x + move_x;
    double new_y = game->player.y + move_y;

    // Check for wall collisions and update player position accordingly
    if (!is_wall(game, new_x, game->player.y))
    {
        game->player.x = new_x;
    }
    if (!is_wall(game, game->player.x, new_y))
    {
        game->player.y = new_y;
    }

	printf("Updated Player Position: x = %f, y = %f\n", game->player.x, game->player.y);
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
	game->skip_mouse_event = 1;
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;

    // Apply rotation using cosine and sine for smooth rotation
    game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);

    game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);

	//TODO fix
	//mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height / 2);
	game->skip_mouse_event = 0;
}

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

void draw_center_circle(t_game *game, int radius)
{
	int center_x;
	int center_y;
	int pixel_x;
	int pixel_y;
	int x;
	int y;

	center_y = game->win_height / 2;
	center_x = game->win_width / 2;
	y = -radius - 1;
	while (++y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius)) // Vérifie si le pixel est dans le cercle
			{
				pixel_x = center_x + x;
				pixel_y = center_y + y;
				if (pixel_x >= 0 && pixel_x < game->win_width && pixel_y >= 0 && pixel_y < game->win_height)
					mlx_pixel_put(game->mlx, game->win, pixel_x, pixel_y, 0x000000);
			}
			x++;
		}
	}
}

void check_portal_teleport(t_game *game) {
    int portal_index = -1;

    // Check if the player is on a portal
    if (game->map.map[(int)game->player.y][(int)game->player.x] == '2') {
        portal_index = 0;
    } else if (game->map.map[(int)game->player.y][(int)game->player.x] == '3') {
        portal_index = 1;
    }

    if (portal_index != -1 && game->portals[portal_index].link) {
        int other_portal = (portal_index == 0) ? 1 : 0;

        // Teleport the player to the other portal's location
        game->player.x = game->portals[other_portal].x + 0.5;
        game->player.y = game->portals[other_portal].y + 0.5;

        // Adjust player direction based on portal orientations
        if (game->portals[portal_index].direction == game->portals[other_portal].direction) {
            // Same direction, do nothing
        } else if (abs(game->portals[portal_index].direction - game->portals[other_portal].direction) == 2) {
            // Opposite directions, rotate 180 degrees
            game->player.dir_x = -game->player.dir_x;
            game->player.dir_y = -game->player.dir_y;
        } else {
            // Rotate 90 degrees based on direction difference
            double old_dir_x = game->player.dir_x;
            if ((game->portals[portal_index].direction == NORTH && game->portals[other_portal].direction == EAST) ||
                (game->portals[portal_index].direction == EAST && game->portals[other_portal].direction == SOUTH) ||
                (game->portals[portal_index].direction == SOUTH && game->portals[other_portal].direction == WEST) ||
                (game->portals[portal_index].direction == WEST && game->portals[other_portal].direction == NORTH)) {
                game->player.dir_x = -game->player.dir_y;
                game->player.dir_y = old_dir_x;
            } else {
                game->player.dir_x = game->player.dir_y;
                game->player.dir_y = -old_dir_x;
            }
        }
    }
}


int display_each_frame(t_game *game)
{
	// Clear the frame
	t_texture frame;
	frame.width = game->win_width;
	frame.height = game->win_height;
	frame.img = mlx_new_image(game->mlx, frame.width, frame.height);
	frame.addr = (int *)mlx_get_data_addr(frame.img, &frame.pixel_bits, &frame.size_line, &frame.endian);
	// Render the scene (walls, floor, ceiling) on the frame
	render_scene(game, &frame);
	update_balls(game);
	draw_ball(game, &frame);
	// Display the rendered frame (this shows the scene)
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	// Draw the minimap on top of the scene
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 10, 10);  // Minimap overlay
	// Draw the center point
	draw_center_circle(game, 5);
	// Clean up the frame resources
	mlx_destroy_image(game->mlx, frame.img);
	// Handle player movement and actions
	is_action(game);
	check_portal_teleport(game);
	display_portal_gun(game);  // Handle gun display
	return 0;
}





