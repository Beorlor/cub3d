/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:22:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 09:15:22 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_ball	*set_up_ball(t_game *game, int button)
{
	t_ball	*ball;

	if (game->ball[0].active || game->ball[1].active)
		return (NULL);  // Prevent shooting if a ball is already active

	if (button == 1)
	{
		ball = &game->ball[0];
		game->ball[1].active = 0;
	}
	else if (button == 3)
	{
		ball = &game->ball[1];
		game->ball[0].active = 0;
	}
	else
	{
		return (NULL);
	}
	return (ball);
}

// Initialize the ball and set its initial positions
void	create_ball(t_game *game, int button)
{
	t_ball	*ball;

	// Prevent shooting if a ball is already active
	if (game->ball[0].active || game->ball[1].active)
		return;

	ball = set_up_ball(game, button);
	if (ball == NULL)
		return;
	if (!ball->active)
	{
		// Initialize ball's real position (map coordinates)
		ball->x = game->player.x;
		ball->y = game->player.y;

		// Initialize ball's window position (screen coordinates)
		ball->wx = (game->win_width / 2) - (ball->texture.width / 2);
		ball->wy = game->win_height - 180;

		ball->size = ball->texture.width;
		ball->stage = 1; // Start at stage 1
		ball->speed = 0.3; // Slow speed for map movement

		// Set the direction based on the player's direction
		ball->direction_x = game->player.dir_x;
		ball->direction_y = game->player.dir_y;

		ball->active = 1;
	}
}

// Move the ball towards the center of the screen (first stage of the animation)
void	move_ball_towards_center(t_game *game, t_ball *ball)
{
	double center_x = game->win_width / 2.0;
	double center_y = game->win_height / 2.0;
	double dx = center_x - (ball->wx + ball->size / 2.0);
	double dy = center_y - (ball->wy + ball->size / 2.0);
	double distance = sqrt(dx * dx + dy * dy);

	// Shrink the ball slightly as it moves towards the center
	ball->size = fmax(5, ball->size - 1);

	if (distance > 100.0)
	{
		ball->wx += (dx / distance) * 20;  // Faster movement to the center
		ball->wy += (dy / distance) * 20;
	}
	else
	{
		// Ensure the ball ends exactly in the center for Stage 2 transition
		ball->wx = center_x - (ball->size / 2.0);
		ball->wy = center_y - (ball->size / 2.0);
		ball->stage = 2; // Move to stage 2
	}
}

// Deactivate the specified portal (blue or orange)
void	deactivate_portal(t_game *game, int portal_index) {
	if (game->portals[portal_index].active) {
		game->map.map[(int)game->portals[portal_index].y][(int)game->portals[portal_index].x] = '1'; // Reset to wall
		game->portals[portal_index].active = 0; // Deactivate the portal
		game->portals[portal_index].link = 0; // Unlink the portal
	}
}

// Unlink both portals
void	unlink_portals(t_game *game) {
	game->portals[0].link = 0;
	game->portals[1].link = 0;
}

// Print portal information for debugging
void	print_portal_info(t_game *game) {
	printf("Blue Portal - x: %.2f, y: %.2f, direction: %d, active: %d, link: %d\n",
		   game->portals[0].x, game->portals[0].y, game->portals[0].direction, game->portals[0].active, game->portals[0].link);
	printf("Orange Portal - x: %.2f, y: %.2f, direction: %d, active: %d, link: %d\n",
		   game->portals[1].x, game->portals[1].y, game->portals[1].direction, game->portals[1].active, game->portals[1].link);
}

// Function to place a portal
void	place_portal(t_game *game, int portal_index, int map_x, int map_y, int direction) {
	//int other_portal_index = (portal_index == 0) ? 1 : 0;

	// Handle blue portal ('2') interaction
	if (portal_index == 0) {
		if (game->map.map[map_y][map_x] == '3') {  // Blue hits orange
			deactivate_portal(game, 0);  // Remove old blue portal
			deactivate_portal(game, 1);  // Remove old orange portal
			unlink_portals(game);  // Unlink both portals
		} else if (game->map.map[map_y][map_x] == '2') {  // Blue hits blue
			game->portals[0].direction = direction;  // Update direction
			return;
		} else if (game->map.map[map_y][map_x] == '1') {  // Blue hits wall
			deactivate_portal(game, 0);  // Remove old blue portal
		}

		// Place the new blue portal
		game->portals[0].active = 1;
		game->portals[0].x = map_x;
		game->portals[0].y = map_y;
		game->portals[0].direction = direction;
		game->map.map[map_y][map_x] = '2';  // Mark as blue portal block

	// Handle orange portal ('3') interaction
	} else if (portal_index == 1) {
		if (game->map.map[map_y][map_x] == '2') {  // Orange hits blue
			deactivate_portal(game, 0);  // Remove old blue portal
			deactivate_portal(game, 1);  // Remove old orange portal
			unlink_portals(game);  // Unlink both portals
		} else if (game->map.map[map_y][map_x] == '3') {  // Orange hits orange
			game->portals[1].direction = direction;  // Update direction
			return;
		} else if (game->map.map[map_y][map_x] == '1') {  // Orange hits wall
			deactivate_portal(game, 1);  // Remove old orange portal
		}

		// Place the new orange portal
		game->portals[1].active = 1;
		game->portals[1].x = map_x;
		game->portals[1].y = map_y;
		game->portals[1].direction = direction;
		game->map.map[map_y][map_x] = '3';  // Mark as orange portal block
	}

	// Check if the two portals are now linked
	if (game->portals[0].active && game->portals[1].active) {
		game->portals[0].link = 1;
		game->portals[1].link = 1;
	} else {
		unlink_portals(game); // Unlink if one portal is deactivated
	}

	// Debug: Print portal values after placing a portal
	print_portal_info(game);
}

// Move the ball towards the wall and place a portal
void move_ball_towards_wall(t_game *game, t_ball *ball)
{
    double next_x = ball->x + ball->direction_x * ball->speed;
    double next_y = ball->y + ball->direction_y * ball->speed;
    int map_x = (int)next_x;
    int map_y = (int)next_y;

    int direction;
    int side; // Track which side the ball hit

    // DDA setup: calculate distances between current and next grid intersections
    double delta_dist_x = fabs(1 / ball->direction_x);
    double delta_dist_y = fabs(1 / ball->direction_y);

    int step_x, step_y;
    double side_dist_x, side_dist_y;

    // Calculate step direction and initial side_dist
    if (ball->direction_x < 0) {
        step_x = -1;
        side_dist_x = (ball->x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - ball->x) * delta_dist_x;
    }

    if (ball->direction_y < 0) {
        step_y = -1;
        side_dist_y = (ball->y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - ball->y) * delta_dist_y;
    }

    // Perform DDA to find the side of the wall the ball hit
    while (1) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0; // Horizontal side (East-West)
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1; // Vertical side (North-South)
        }

        // Check if the ball hits a wall, door, blue portal, or orange portal
        if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height ||
            game->map.map[map_y][map_x] == '1' || game->map.map[map_y][map_x] == '2' || game->map.map[map_y][map_x] == '3') {

            // If it's not a door, proceed with portal creation
            if (game->map.map[map_y][map_x] != 'D') {
                // Determine the direction of the hit side
                if (side == 0) {
                    direction = (step_x > 0) ? EAST : WEST; // Ball hit East or West side
                } else {
                    direction = (step_y > 0) ? SOUTH : NORTH; // Ball hit North or South side
                }

                // Place the portal on the correct wall side
                int portal_index = (ball == &game->ball[0]) ? 0 : 1; // Determine portal index: 0 for blue, 1 for orange
                place_portal(game, portal_index, map_x, map_y, direction);
            }
            ball->active = 0; // Deactivate the ball after placing the portal or hitting the door
            return;
        }

        // Check if the ball hits a door ('D')
        if (game->map.map[map_y][map_x] == 'D') {
            // Treat the door as a wall only if the player is near
            if (is_player_next_to_door(game, map_x, map_y)) {
                printf("Door hit by ball at map coordinates x = %d, y = %d\n", map_x, map_y);
                ball->active = 0; // Deactivate the ball without creating a portal
                return;
            }
        }
    }

    // Update ball position on the map
    ball->x = next_x;
    ball->y = next_y;

    // Shrink the ball as it moves
    ball->size = fmax(5, ball->size - 4);
}

// Update the state of the balls
void	update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			if (game->ball[i].stage == 1)
				move_ball_towards_center(game, &game->ball[i]);
			else if (game->ball[i].stage == 2)
				move_ball_towards_wall(game, &game->ball[i]);
		}
		i++;
	}
}

// Load the textures for the balls
void	load_ball_textures(t_game *game)
{
	game->ball[0].texture.img = mlx_xpm_file_to_image(game->mlx,
			"src/sprites/sprites/orange_ball.xpm", &game->ball[0].texture.width,
			&game->ball[0].texture.height);
	if (!game->ball[0].texture.img)
	{
		printf("Failed to load orange ball texture\n");
		free_all2(game);
	}
	game->ball[0].texture.addr = (int *)mlx_get_data_addr(
			game->ball[0].texture.img, &game->ball[0].texture.pixel_bits,
			&game->ball[0].texture.size_line, &game->ball[0].texture.endian);
	game->ball[1].texture.img = mlx_xpm_file_to_image(game->mlx,
			"src/sprites/sprites/blue_ball2.xpm", &game->ball[1].texture.width,
			&game->ball[1].texture.height);
	if (!game->ball[1].texture.img)
	{
		printf("Failed to load blue ball texture\n");
		free_all2(game);
	}
	game->ball[1].texture.addr = (int *)mlx_get_data_addr(
			game->ball[1].texture.img, &game->ball[1].texture.pixel_bits,
			&game->ball[1].texture.size_line, &game->ball[1].texture.endian);
}

void	draw_ball(t_game *game, t_texture *frame)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (game->ball[i].active)
		{
			int tex_width = game->ball[i].texture.width;
			int tex_height = game->ball[i].texture.height;

			// Calculate the scale factor based on the current ball size
			double scale_x = (double)game->ball[i].size / tex_width;
			double scale_y = (double)game->ball[i].size / tex_height;

			// Determine start_x and start_y based on the stage
			int start_x, start_y;

			if (game->ball[i].stage == 1) {
				// Stage 1: Centered horizontally in the screen, moving vertically towards the center
				start_x = (game->win_width / 2) - (game->ball[i].size / 2);
				start_y = game->ball[i].wy - (game->ball[i].size / 2);
			} else if (game->ball[i].stage == 2) {
				// Stage 2: Centered based on wx and wy, representing its position in the world
				start_x = (game->win_width / 2) - (game->ball[i].size / 2);
				start_y = (game->win_width / 2) - (game->ball[i].size / 2);
			}

			// Loop through each pixel of the screen where the ball should be drawn
			for (int y = 0; y < game->ball[i].size; y++)
			{
				for (int x = 0; x < game->ball[i].size; x++)
				{
					// Calculate the corresponding position in the texture
					int tex_x = (int)(x / scale_x);
					int tex_y = (int)(y / scale_y);

					// Ensure the texture coordinates are within bounds
					if (tex_x >= 0 && tex_x < tex_width && tex_y >= 0 && tex_y < tex_height)
					{
						// Get the color from the texture
						int color = game->ball[i].texture.addr[tex_y * tex_width + tex_x];

						// Calculate the position to draw the pixel on the screen
						int screen_x = start_x + x;
						int screen_y = start_y + y;

						// Skip rendering if the pixel is black or fully transparent
						if (screen_x >= 0 && screen_x < game->win_width && screen_y >= 0 && screen_y < game->win_height && (color & 0xFFFFFF) != 0x000000)
						{
							my_mlx_pixel_put(frame, screen_x, screen_y, color);
						}
					}
				}
			}
		}
		i++;
	}
}
