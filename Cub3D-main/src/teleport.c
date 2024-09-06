/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:52:04 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:11:38 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// Cooldown time after teleport (in frames or ticks)
#define TELEPORT_COOLDOWN 200
#define TELEPORT_TRIGGER_ZONE 1.0 // Extended zone for debugging

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
