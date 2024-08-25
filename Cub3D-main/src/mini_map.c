
#include "../cub3D.h"

void draw_pixel(t_texture *mini_map, int x, int y, int color)
{
    if (x >= 0 && x < mini_map->width && y >= 0 && y < mini_map->height)
    {
        mini_map->addr[y * mini_map->width + x] = color;
    }
}

void draw_mini_map(t_game *game)
{
    int x, y;
    int map_x, map_y;

    // Iterate over each pixel of the minimap
    for (y = 0; y < game->mini_map.height; y++)
    {
        for (x = 0; x < game->mini_map.width; x++)
        {
            // Calculate corresponding map coordinates
            map_x = (int)((game->player.x - game->mini_map.width / 2 / T_SIZE) + x / T_SIZE);
            map_y = (int)((game->player.y - game->mini_map.height / 2 / T_SIZE) + y / T_SIZE);

            // Check map boundaries and draw walls or empty spaces
            if (map_x >= 0 && map_x < game->map.width && map_y >= 0 && map_y < game->map.height)
            {
                if (game->map.map[map_y][map_x] == '1')
                    draw_pixel(&game->mini_map, x, y, 0xFFFFFF); // Wall in white
                else
                    draw_pixel(&game->mini_map, x, y, 0x888888); // Empty space in gray
            }
            else
            {
                draw_pixel(&game->mini_map, x, y, 0x555555); // Out of bounds in dark gray
            }
        }
    }

    // Draw the player as a bigger square (6x6 pixels) in the minimap's center
    int player_size = 6; // Adjust the size of the player on the minimap
    for (int i = -player_size / 2; i <= player_size / 2; i++)
    {
        for (int j = -player_size / 2; j <= player_size / 2; j++)
        {
            draw_pixel(&game->mini_map, game->mini_map.width / 2 + i, game->mini_map.height / 2 + j, 0xFF0000); // Player in red
        }
    }
}

void    draw(t_texture *img, int x, int y, int color)
{
    int i;
    int j;
    double pixel_x;
    double pixel_y;

    i = 0;
    while (i < T_SIZE)
    {
        j = 0;
        while (j < T_SIZE)
        {
            pixel_x = x * T_SIZE + j;
            pixel_y = y * T_SIZE + i;
            if (pixel_x < img->width && pixel_y < img->height)
                my_mlx_pixel_put(img, (int)pixel_x, (int)pixel_y, color);
            j++;
        }
        i++;
    }
}

void draw_player(t_game *game, t_texture *mini_map)
{
    int player_x = M_SIZE / 2;
    int player_y = M_SIZE / 2;

    // Draw the player as a small red square
    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            draw(mini_map, player_x + j, player_y + i, 0xFF0000); // Red color for the player
        }
    }

    // Draw the player's view direction
    draw_view_direction(game, mini_map);
}


int is_wall(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    // Check boundaries and return if it's a wall
    if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height)
        return 1; // Out of bounds treated as a wall
    if (game->map.map[map_y][map_x] == '1')
        return 1; // Wall
    return 0; // No wall
}



void draw_view_direction(t_game *game, t_texture *mini_map)
{
    double map_x, map_y;
    double player_x = M_SIZE / 2 * T_SIZE;
    double player_y = M_SIZE / 2 * T_SIZE;

    // Draw a line representing the player's view direction
    for (int i = 0; i < 40; i++)
    {
        map_x = player_x + i * game->player.dir_x;
        map_y = player_y + i * game->player.dir_y;

        if (is_wall(game, (int)(game->player.x + i * game->player.dir_x), (int)(game->player.y + i * game->player.dir_y)))
            break;

        draw(mini_map, (int)(map_x / T_SIZE), (int)(map_y / T_SIZE), 0xFF0000); // Red color for the direction
    }
}

void my_mlx_pixel_put(t_texture *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        dst = (char *)img->addr + (y * img->size_line + x * (img->pixel_bits / 8));
        *(unsigned int *)dst = color;
    }
}


/*
FAIRE UN DEUXIEME JEU A PART :
- Prendre map parsé
- Prendre position joueur
- Quand portail passé on réaffiche tout (refaire fonction rendering)
=> Réappeler la fonction qui affiche la map.
*/
