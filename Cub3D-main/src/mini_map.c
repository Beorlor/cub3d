
#include "../cub3D.h"

void    draw_mini_map(t_game *game, t_texture *mini_map)
{
    double  x;
    double  y;
    double map_x;
    double map_y;

    y = 0;
    while (y < M_SIZE)
    {
        x = 0;
        while (x < M_SIZE)
        {
            map_x = game->player.x - (M_SIZE / 2) + x;
            map_y = game->player.y - (M_SIZE / 2) + y;
            if (map_x >= 0 && map_x < game->map.width && map_y >= 0 && map_y < game->map.height)
            {
                if (game->map.map[(int)map_y][(int)map_x] == '1')
                    draw(mini_map, x, y, 0xFFFFFF);
                else if (game->map.map[(int)map_y][(int)map_x] == '0' || game->map.map[(int)map_y][(int)map_x] == 'N'
                    || game->map.map[(int)map_y][(int)map_x] == 'E' || game->map.map[(int)map_y][(int)map_x] == 'W'
                    || game->map.map[(int)map_y][(int)map_x] == 'S')
                    draw(mini_map, (int)x, (int)y, 0x888888);
                else
                    draw(mini_map, (int)x, (int)y, 0x000000);
            }
            else
                draw(mini_map, (int)x, (int)y, 0x555555); // Outside of map
            x++;
        }
        y++;
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

void    draw_player(t_game *game, t_texture *mini_map)
{
    double player_x;
    double player_y;
    double pixel_x;
    double pixel_y;
    int i;
    int j;

    player_x = M_SIZE / 2 * T_SIZE;
    player_y = M_SIZE / 2 * T_SIZE;
    i = 0;
    while (i < 6) // Parcourir 6 pixels pour former le square (height)
    {
        j = 0;
        while (j < 6) // (width)
        {
            pixel_x = player_x + j;
            pixel_y = player_y + i;
            if (pixel_x >= 0 && pixel_x < mini_map->width && pixel_y >= 0 && pixel_y < mini_map->height)
                my_mlx_pixel_put(mini_map, (int)pixel_x, (int)pixel_y, 0xFF0000); // Red for player
            j++;
        }
        i++;
    }
    draw_view_direction(game, mini_map);
}


int is_wall(t_game *game, int map_x, int map_y)
{

    if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height)
        return (1);
    else if (game->map.map[map_y][map_x] == '1')
        return (1);
    return (0);
}

void    draw_view_direction(t_game *game, t_texture *mini_map)
{
    double map_x;
    double map_y;
    double player_x;
    double player_y;
    double x;
    double y;
    int i;

    i = 0;
    player_x = M_SIZE / 2 * T_SIZE; // As the position of player in MP is the center, it'll also be the start position of the ray.
    player_y = M_SIZE / 2 * T_SIZE;
    while (i < 40)
    {
        x = player_x + i * game->player.dir_x;
        y = player_y + i * game->player.dir_y;
        map_x = (game->player.x - M_SIZE / 2) + (x / T_SIZE); // Convert MP position (above) to map coordonates.
        map_y = (game->player.y - M_SIZE / 2) + (y / T_SIZE); // In order to check in the real map if there is walls, etc.
        if (is_wall(game, (int)map_x, (int)map_y) == 1)
            break ;
        else
            my_mlx_pixel_put(mini_map, (int)x, (int)y, 0xFF0000);
        i++;
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