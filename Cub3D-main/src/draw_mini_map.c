/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:57:58 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 13:15:24 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player(t_game *game, t_texture *mini_map)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = M_SIZE / 2;
	player_y = M_SIZE / 2;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			draw(mini_map, player_x + j, player_y + i, 0xFF0000);
			j++;
		}
		i++;
	}
	draw_view_direction(game, mini_map);
}

void	draw_view_direction(t_game *game, t_texture *mini_map)
{
	double	map_x;
	double	map_y;
	double	player_x;
	double	player_y;
	int		i;

	player_x = M_SIZE / 2 * T_SIZE;
	player_y = M_SIZE / 2 * T_SIZE;
	i = 0;
	while (i < 40)
	{
		map_x = player_x + i * game->player.dir_x;
		map_y = player_y + i * game->player.dir_y;
		if (is_wall(game, (int)(game->player.x + i * game->player.dir_x),
			(int)(game->player.y + i * game->player.dir_y)))
			break ;
		draw(mini_map, (int)(map_x / T_SIZE), (int)(map_y / T_SIZE), 0xFF0000);
		i++;
	}
}

void	my_mlx_pixel_put(t_texture *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = (char *)img->addr + (y * img->size_line + x * (img->pixel_bits
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_mini_map_pixel_color(t_game *game, char map_char, int x, int y)
{
	int	color;

	if (map_char == '1')
		color = 0xFFFFFF;
	else if (map_char == 'D')
		color = 0x00FF00;
	else if (map_char == '2')
		color = 0x0000FF;
	else if (map_char == '3')
		color = 0xFFA500;
	else
		color = 0x888888;
	draw_pixel(&game->mini_map, x, y, color);
}

void	draw_mini_map_pixel(t_game *game, int y)
{
	int	x;
	int	map_x;
	int	map_y;

	x = 0;
	while (x < game->mini_map.width)
	{
		map_x = (int)((game->player.x - game->mini_map.width / 2 / T_SIZE) + x
				/ T_SIZE);
		map_y = (int)((game->player.y - game->mini_map.height / 2 / T_SIZE) + y
				/ T_SIZE);
		if (map_x >= 0 && map_x < game->map.width && map_y >= 0
			&& map_y < game->map.height)
		{
			draw_mini_map_pixel_color(game, game->map.map[map_y][map_x], x, y);
		}
		else
		{
			draw_pixel(&game->mini_map, x, y, 0x555555);
		}
		x++;
	}
}

// Iterate over each pixel of the minimap
// Calculate corresponding map coordinates
// Check map boundaries and draw walls, doors, or empty spaces
void	draw_mini_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->mini_map.height)
	{
		draw_mini_map_pixel(game, y);
		y++;
	}
	draw_mini_map_player(game);
}
