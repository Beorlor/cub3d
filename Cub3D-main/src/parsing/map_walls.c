/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:51:29 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 16:19:25 by jeguerin         ###   ########.fr       */
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

// Map to free !
int	are_walls_valid(t_game *game)
{
	char	**map;
	int		i;

	map = get_map(game);
	if (map == NULL)
		return (printf("Can't copy map\n"), 1);
	if (flood_fill(game, map, game->player.x, game->player.y) == 1)
		return (printf("Map is not surrounded by walls\n"), 1);
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
			return (printf("X: %d\n", x), printf("Y: %d\n", y), 1);
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

// int flood_fill(t_game *game, char **map, int x, int y)
// {
//     if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
//         return 1; // Hors limites
//     if (map[y][x] == '1' || map[y][x] == 'X')
//         return 0; // Case visitée ou mur
//     if (map[y][x] == '0')
//     {
//         if ((y > 0 && map[y - 1][x] == ' ') ||
//             (y < game->map.height - 1 && map[y + 1][x] == ' ') ||
//             (x > 0 && map[y][x - 1] == ' ') || // Case à gauche
//             (x < game->map.width - 1 && map[y][x + 1] == ' '))
//             return 1; // Contact avec un espace vide
//     }
//     map[y][x] = 'X';
//     if (flood_fill(game, map, y - 1, x) == 1 ||
//         flood_fill(game, map, y + 1, x) == 1 ||
//         flood_fill(game, map, y, x - 1) == 1 ||
//         flood_fill(game, map, y, x + 1) == 1)
//         return 1;
//     return 0;
// }
