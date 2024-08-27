#include "../cub3D.h"

void render_scene(t_game *game, t_texture *frame) {
    int ceiling_color = (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b;
    int floor_color = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;

	printf("%d %d\n", game->win_height, game->win_width);
    for (int y = 0; y < game->win_height / 2; y++) {
        for (int x = 0; x < game->win_width; x++) {
            my_mlx_pixel_put(frame, x, y, ceiling_color);  // Draw ceiling
        }
    }

    for (int y = game->win_height / 2; y < game->win_height; y++) {
        for (int x = 0; x < game->win_width; x++) {
            my_mlx_pixel_put(frame, x, y, floor_color);  // Draw floor
        }
    }
}


