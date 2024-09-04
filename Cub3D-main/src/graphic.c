/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:18:07 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 15:18:10 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void render_scene(t_game *game, t_texture *frame) {
    int ceiling_color = (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b;
    int floor_color = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;

    // Apply the walking offset to the rendering
    int walk_offset = game->walk_offset;

    // Draw the ceiling with walking offset
    for (int y = 0; y < game->win_height / 2 + walk_offset; y++) {
        for (int x = 0; x < game->win_width; x++) {
            my_mlx_pixel_put(frame, x, y, ceiling_color);
        }
    }

    // Draw the floor with walking offset
    for (int y = game->win_height / 2 + walk_offset; y < game->win_height; y++) {
        for (int x = 0; x < game->win_width; x++) {
            my_mlx_pixel_put(frame, x, y, floor_color);
        }
    }

    // Raycasting to draw the walls, doors, and portals
    for (int x = 0; x < game->win_width; x++) {
        // Calculate ray position and direction
        double camera_x = (2 * x / (double)game->win_width - 1) / 2;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        // Map position
        int map_x = (int)game->player.x;
        int map_y = (int)game->player.y;

        // Length of ray from one x or y-side to next x or y-side
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // Step and initial side_dist
        int step_x, step_y;
        double side_dist_x, side_dist_y;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }

        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }

        // Perform DDA (Digital Differential Analysis)
        int hit = 0;  // Was there a wall, door, or portal hit?
        int side;     // Was a NS or a EW wall hit?

        while (hit == 0) {
            // Jump to next map square, either in x-direction, or in y-direction
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Check if ray has hit a wall, door, or portal
            if (game->map.map[map_y][map_x] == '1' ||
                game->map.map[map_y][map_x] == 'D' ||
                game->map.map[map_y][map_x] == '2' || game->map.map[map_y][map_x] == '3') {
                hit = 1;  // Wall, door, or portal hit
            }
        }

        // Calculate distance projected on camera direction (perpendicular distance)
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate height of line to draw on screen
        int line_height = (int)(game->win_height / perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe, adjusted with walk offset
        int draw_start = -line_height / 2 + game->win_height / 2 + walk_offset;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + game->win_height / 2 + walk_offset;
        if (draw_end >= game->win_height) draw_end = game->win_height - 1;

        // Determine the texture based on what was hit (wall, door, or portal)
        t_texture *texture;
        t_texture *overlay_texture = NULL;

        if (side == 0) {
            texture = (step_x > 0) ? &game->textures[EAST] : &game->textures[WEST];
        } else {
            texture = (step_y > 0) ? &game->textures[SOUTH] : &game->textures[NORTH];
        }

        // Adjust portal overlay based on which side was hit and portal's direction
        if (game->map.map[map_y][map_x] == '2') {
            if ((side == 0 && game->portals[0].direction == (step_x > 0 ? EAST : WEST)) ||
                (side == 1 && game->portals[0].direction == (step_y > 0 ? SOUTH : NORTH))) {
                overlay_texture = &game->portals[0].texture;  // Use blue portal texture
            }
        } else if (game->map.map[map_y][map_x] == '3') {
            if ((side == 0 && game->portals[1].direction == (step_x > 0 ? EAST : WEST)) ||
                (side == 1 && game->portals[1].direction == (step_y > 0 ? SOUTH : NORTH))) {
                overlay_texture = &game->portals[1].texture;  // Use orange portal texture
            }
        }

        // Calculate the exact position where the wall/portal was hit
        double wall_x;
        if (side == 0)
            wall_x = game->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // X coordinate on the texture
        int tex_x = (int)(wall_x * (double)texture->width);
        if (tex_x < 0) tex_x = 0;
        if (tex_x >= texture->width) tex_x = texture->width - 1;

        // Fix the texture direction issue
        if (side == 0 && step_x < 0) tex_x = texture->width - tex_x - 1;
        if (side == 1 && step_y > 0) tex_x = texture->width - tex_x - 1;

        // Draw the wall with the texture
        for (int y = draw_start; y < draw_end; y++) {
            // Calculate the y-coordinate on the texture, considering walk offset
            int tex_y = (((y - walk_offset) * 256 - game->win_height * 128 + line_height * 128) * texture->height) / line_height / 256;

            if (tex_y < 0) tex_y = 0;
            if (tex_y >= texture->height) tex_y = texture->height - 1;

            // Get the color from the texture
            int color = texture->addr[tex_y * texture->width + tex_x];

            // Darken the color if it's a side wall (for a shading effect)
            if (side == 1) color = (color >> 1) & 0x7F7F7F;

            // Draw the wall pixel
            my_mlx_pixel_put(frame, x, y, color);

            // If a portal is supposed to be drawn, overlay it
            if (overlay_texture) {
                // Calculate the coordinates on the portal texture
                int overlay_tex_x = (int)(wall_x * (double)overlay_texture->width);
                if (overlay_tex_x < 0) overlay_tex_x = 0;
                if (overlay_tex_x >= overlay_texture->width) overlay_tex_x = overlay_texture->width - 1;

                int overlay_tex_y = (((y - walk_offset) * 256 - game->win_height * 128 + line_height * 128) * overlay_texture->height) / line_height / 256;

                if (overlay_tex_y < 0) overlay_tex_y = 0;
                if (overlay_tex_y >= overlay_texture->height) overlay_tex_y = overlay_texture->height - 1;

                int overlay_color = overlay_texture->addr[overlay_tex_y * overlay_texture->width + overlay_tex_x];

                // Only draw the portal texture if the pixel is not black
                if ((overlay_color & 0xFFFFFF) != 0x000000) {
                    my_mlx_pixel_put(frame, x, y, overlay_color);
                }
            }
        }
    }
}
