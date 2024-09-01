/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:52:26 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 18:21:26 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	it_is_out(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width
		|| y < 0 || y >= game->map.height)
		return (1);
	return (0);
}

int	check_door(t_game *game, int i, int j)
{
	if (it_is_out(game, j, i) != 1 && game->map.map[i][j - 1] == '1'
		&& game->map.map[i][j + 1] == '1'
		&& game->map.map[i - 1][j] == '0'
		&& game->map.map[i + 1][j] == '0')
		return (1);
	else if (it_is_out(game, j, i) != 1
		&& game->map.map[i - 1][j] == '1'
		&& game->map.map[i + 1][j] == '1'
		&& game->map.map[i][j - 1] == '0'
		&& game->map.map[i][j + 1] == '0')
		return (1);
	return (0);
}

int	door_error(t_game *game, int door, int value)
{
    if (door > 1)
		return (printf("There are too many doors\n"), free_all2(game));
	else if (value == 1)
		return (0);
	return (-1);
}

int	is_door_valid(t_game *game)
{
	int	i;
	int	j;
	int	door;
	int	value;

	i = -1;
	door = 0;
	value = 0;
	while (game->map.map[++i])
	{
		j = 0;
		while (game->map.map[j])
		{
			if (game->map.map[i][j] == 'D')
			{
				if (check_door(game, i, j) == 1)
					value = 1;
				door++;
			}
			j++;
		}
	}
	if (door_error(game, door, value) == 0)
		return (0);
	return (printf("Door is not well placed\n"), 1);
}
