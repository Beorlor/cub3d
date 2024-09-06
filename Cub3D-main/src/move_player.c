/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:43:11 by jeguerin         ###   ########.fr       */
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
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->skip_mouse_event = 1;
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y
		* sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
	mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height
		/ 2);
	game->skip_mouse_event = 0;
}

void	draw_center_circle(t_game *game, int radius)
{
	int	p_x;
	int	p_y;
	int	x;
	int	y;

	y = -radius - 1;
	while (++y <= radius)
	{
		x = -radius - 1;
		while (++x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
			{
				p_x = (game->win_width / 2) + x;
				p_y = (game->win_height / 2) + y;
				if (p_x >= 0 && p_x < game->win_width && p_y >= 0
					&& p_y < game->win_height)
					mlx_pixel_put(game->mlx, game->win, p_x, p_y, 0x000000);
			}
		}
	}
}

// Update the display_each_frame function
int	display_each_frame(t_game *game)
{
	t_texture	frame;

	frame.width = game->win_width;
	frame.height = game->win_height;
	frame.img = mlx_new_image(game->mlx, frame.width, frame.height);
	frame.addr = (int *)mlx_get_data_addr(frame.img, &frame.pixel_bits,
			&frame.size_line, &frame.endian);
	render_scene(game, &frame);
	update_balls(game);
	draw_ball(game, &frame);
	display_portal_gun(game, &frame);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 10, 10);
	draw_center_circle(game, 5);
	mlx_destroy_image(game->mlx, frame.img);
	is_action(game);
	check_portal_teleport(game);
	return (0);
}
