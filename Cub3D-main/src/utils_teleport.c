/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_teleport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:53:35 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 17:46:43 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
