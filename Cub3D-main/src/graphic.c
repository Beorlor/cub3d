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

    // Raycasting to draw the walls
    for (int x = 0; x < game->win_width; x++) {
        // Calculate ray position and direction
        double camera_x = (2 * x / (double)game->win_width - 1) / 3;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		//printf("%f %f %f %f %f\n", game->player.plane_x, game->player.plane_y, camera_x, ray_dir_x, ray_dir_y);

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
        int hit = 0;  // Was there a wall hit?
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
            // Check if ray has hit a wall
            if (game->map.map[map_y][map_x] == '1') hit = 1;
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

        // Determine texture index based on wall hit direction
        int texture_index;
        if (side == 0) {
            texture_index = (step_x > 0) ? EAST : WEST;
        } else {
            texture_index = (step_y > 0) ? SOUTH : NORTH;
        }

        // Calculate the exact position where the wall was hit
        double wall_x;
        if (side == 0)
            wall_x = game->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // X coordinate on the texture
        int tex_x = (int)(wall_x * (double)game->textures[texture_index].width);
        if (tex_x < 0) tex_x = 0;
        if (tex_x >= game->textures[texture_index].width) tex_x = game->textures[texture_index].width - 1;

        // Fix the texture direction issue
        if (side == 0 && step_x < 0) tex_x = game->textures[texture_index].width - tex_x - 1;
        if (side == 1 && step_y > 0) tex_x = game->textures[texture_index].width - tex_x - 1;

        // Draw the wall with texture
        for (int y = draw_start; y < draw_end; y++) {
            // Calculate the y-coordinate on the texture, considering walk offset
            int tex_y = (((y - walk_offset) * 256 - game->win_height * 128 + line_height * 128) * game->textures[texture_index].height) / line_height / 256;

            if (tex_y < 0) tex_y = 0;
            if (tex_y >= game->textures[texture_index].height) tex_y = game->textures[texture_index].height - 1;

            // Get the color from the texture
            int color = game->textures[texture_index].addr[tex_y * game->textures[texture_index].width + tex_x];

            // Darken the color if it's a side wall (for a shading effect)
            if (side == 1) color = (color >> 1) & 0x7F7F7F;

            // Draw the pixel
            my_mlx_pixel_put(frame, x, y, color);
        }
    }
}
