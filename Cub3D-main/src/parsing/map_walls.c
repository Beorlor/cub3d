/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:51:29 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 16:40:42 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char	**get_map(t_game *game)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!map)
		return (printf("Can't malloc the map\n"), NULL);
	i = 0;
	while (i < game->map.height)
	{
		map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	are_walls_valid(t_game *game)
{
	char	**map;

	map = get_map(game);
	if (map == NULL)
		return (printf("Can't copy map\n"), free_map(map), 1);
	if (flood_fill(game, map, game->player.x, game->player.y) == 1)
		return (printf("Map is not surrounded by walls\n"), free_map(map), 1);
	free_map(map);
	return (0);
}

int	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if (map[y][x] == '0')
	{
		if ((y > 0 && map[y - 1][x] == ' ')
			|| (y < game->map.height - 1 && map[y + 1][x] == ' ')
			|| (x > 0 && map[y][x - 1] == ' ')
			|| (x < game->map.width - 1 && map[y][x + 1] == ' '))
			return (1);
	}
	map[y][x] = 'X';
	if (flood_fill(game, map, x - 1, y - 1) == 1
		|| flood_fill(game, map, x, y - 1) == 1
		|| flood_fill(game, map, x + 1, y - 1) == 1
		|| flood_fill(game, map, x - 1, y) == 1
		|| flood_fill(game, map, x + 1, y) == 1
		|| flood_fill(game, map, x - 1, y + 1) == 1
		|| flood_fill(game, map, x, y + 1) == 1
		|| flood_fill(game, map, x + 1, y + 1) == 1)
		return (1);
	return (0);
}

void	add_spaces_to_map(t_game *game)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (i < game->map.height)
	{
		str = malloc(sizeof(char) * (game->map.width + 1));
		j = 0;
		while (game->map.map[i][j])
		{
			str[j] = game->map.map[i][j];
			j++;
		}
		while (j < game->map.width)
		{
			str[j] = ' ';
			j++;
		}
		str[j] = '\0';
		free(game->map.map[i]);
		game->map.map[i] = str;
		str = NULL;
		i++;
	}
}
