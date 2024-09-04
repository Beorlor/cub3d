/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 20:14:52 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	update_position(t_game *game, double move_x, double move_y)
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
	printf("Updated Player Position: x = %f, y = %f\n",
		game->player.x, game->player.y);
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

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->skip_mouse_event = 1;
	game->player.dir_x = old_dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
	//TODO fix
	mlx_mouse_move(game->mlx, game->win, game->win_width / 2,
		game->win_height / 2);
	game->skip_mouse_event = 0;
}

void	draw_center_circle(t_game *game, int radius)
{
	int	center_x;
	int	center_y;
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;

	center_y = game->win_height / 2;
	center_x = game->win_width / 2;
	y = -radius - 1;
	while (++y <= radius)
	{
		x = -radius - 1;
		while (++x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
			{
				pixel_x = center_x + x;
				pixel_y = center_y + y;
				if (pixel_x >= 0 && pixel_x < game->win_width && pixel_y >= 0
					&& pixel_y < game->win_height)
					mlx_pixel_put(game->mlx, game->win, pixel_x,
						pixel_y, 0x000000);
			}
		}
	}
}

// Cooldown time after teleport (in frames or ticks)
#define TELEPORT_COOLDOWN 50

void	check_portal_teleport(t_game *game)
{
	static int teleport_cooldown = 0;

	// Decrease the cooldown counter if active
	if (teleport_cooldown > 0) {
		teleport_cooldown--;
		return;  // No teleportation while in cooldown
	}

	int portal_index = -1;

	// Check if the player is near a portal's side
	if (game->map.map[(int)game->player.y][(int)game->player.x] == '2') {
		if (fabs(game->player.x - game->portals[0].x) < 0.5 && fabs(game->player.y - game->portals[0].y) < 0.5) {
			portal_index = 0;
		}
	} else if (game->map.map[(int)game->player.y][(int)game->player.x] == '3') {
		if (fabs(game->player.x - game->portals[1].x) < 0.5 && fabs(game->player.y - game->portals[1].y) < 0.5) {
			portal_index = 1;
		}
	}

	if (portal_index != -1 && game->portals[portal_index].link) {
		int other_portal = (portal_index == 0) ? 1 : 0;

		// Calculate direction offsets
		double dx = 0.0;
		double dy = 0.0;
		if (game->portals[portal_index].direction == NORTH) dy = -0.5;
		if (game->portals[portal_index].direction == SOUTH) dy = 0.5;
		if (game->portals[portal_index].direction == EAST) dx = 0.5;
		if (game->portals[portal_index].direction == WEST) dx = -0.5;

		// Check if the player is close enough to the portal to teleport
		if (fabs(game->player.x - (game->portals[portal_index].x + dx)) < 0.1 &&
			fabs(game->player.y - (game->portals[portal_index].y + dy)) < 0.1) {

			// Teleport the player to the other portal's location
			game->player.x = game->portals[other_portal].x + 0.5;
			game->player.y = game->portals[other_portal].y + 0.5;

			// Adjust player direction based on portal orientations
			if (game->portals[portal_index].direction == game->portals[other_portal].direction) {
				// Same direction, no change needed
			} else if (abs(game->portals[portal_index].direction - game->portals[other_portal].direction) == 2) {
				// Opposite directions, rotate 180 degrees
				game->player.dir_x = -game->player.dir_x;
				game->player.dir_y = -game->player.dir_y;
			} else {
				// Rotate 90 degrees based on the direction difference
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

			// Set a small teleport offset to avoid stepping back into the portal
			game->player.x += game->player.dir_x * 0.2;
			game->player.y += game->player.dir_y * 0.2;

			// Activate the teleport cooldown
			teleport_cooldown = TELEPORT_COOLDOWN;

			// Debug: Print player position and direction after teleport
			printf("Teleported to Portal %d. New Position: x = %.2f, y = %.2f. Direction: dir_x = %.2f, dir_y = %.2f\n",
				   other_portal, game->player.x, game->player.y, game->player.dir_x, game->player.dir_y);
		}
	}
}

int	display_each_frame(t_game *game)
{
	t_texture	frame;

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
	return (0);
}
