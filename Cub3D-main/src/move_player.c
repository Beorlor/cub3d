/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 14:05:04 by jedurand         ###   ########.fr       */
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
	printf("Updated Player Position: x = %f, y = %f\n", game->player.x,
		game->player.y);
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

// Cooldown time after teleport (in frames or ticks)
#define TELEPORT_COOLDOWN 500
#define TELEPORT_TRIGGER_ZONE 1.0 // Extended zone for debugging

void	decrease_teleport_cooldown(t_game *game)
{
	if (game->teleport_cooldown > 0)
		game->teleport_cooldown--;
}

int	is_teleport_on_cooldown(t_game *game)
{
	return (game->teleport_cooldown > 0);
}

void	set_teleport_direction(t_portal *portal, double *dx, double *dy)
{
	*dx = 0.0;
	*dy = 0.0;
	if (portal->direction == NORTH)
		*dy = 1.0;
	else if (portal->direction == SOUTH)
		*dy = -1.0;
	else if (portal->direction == EAST)
		*dx = -1.0;
	else if (portal->direction == WEST)
		*dx = 1.0;
}

int	is_player_in_teleport_zone(t_game *game, t_portal *portal, double dx,
		double dy)
{
	return (fabs(game->player.x - (portal->x + dx)) < TELEPORT_TRIGGER_ZONE
		&& fabs(game->player.y - (portal->y + dy)) < TELEPORT_TRIGGER_ZONE);
}

int	find_active_portal(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < 2)
	{
		if (game->portals[i].active)
		{
			set_teleport_direction(&game->portals[i], &dx, &dy);
			if (is_player_in_teleport_zone(game, &game->portals[i], dx, dy))
				return (i);
		}
		i++;
	}
	return (-1);
}

void	teleport_player(t_game *game, int other_portal)
{
	if (game->portals[other_portal].direction == NORTH)
	{
		game->player.x = game->portals[other_portal].x + 0.5;
		game->player.y = game->portals[other_portal].y + 1.5;
	}
	else if (game->portals[other_portal].direction == SOUTH)
	{
		game->player.x = game->portals[other_portal].x + 0.5;
		game->player.y = game->portals[other_portal].y - 0.5;
	}
	else if (game->portals[other_portal].direction == EAST)
	{
		game->player.x = game->portals[other_portal].x - 0.5;
		game->player.y = game->portals[other_portal].y + 0.5;
	}
	else if (game->portals[other_portal].direction == WEST)
	{
		game->player.x = game->portals[other_portal].x + 1.5;
		game->player.y = game->portals[other_portal].y + 0.5;
	}
	game->teleport_cooldown = TELEPORT_COOLDOWN;
}

void	check_portal_teleport(t_game *game)
{
	int	portal_index;
	int	other_portal;

	decrease_teleport_cooldown(game);
	if (is_teleport_on_cooldown(game))
		return ;
	portal_index = find_active_portal(game);
	if (portal_index != -1 && game->portals[portal_index].link)
	{
		if (portal_index == 0)
			other_portal = 1;
		else
			other_portal = 0;
		teleport_player(game, other_portal);
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
