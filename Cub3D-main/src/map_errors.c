/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:00 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 15:52:24 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_map_empty(t_game *game)
{
	size_t	i;
	int		empty_map;

	i = 0;
	empty_map = 0;
	while (game->map.map[i])
	{
		if (game->map.map[i] == NULL)
			empty_map++;
		i++;
	}
	if (empty_map == game->map.height)
	{
		printf("Map is empty\n");
		return (1);
	}
	return (0);
}

int	is_player_here(int player)
{
	if (player > 1)
		return (printf("Map has more than one player\n"), 1);
	else if (player == 0)
		return (printf("Map has no player position (N, S, E, W)\n"), 1);
	return (0);
}

void	set_up_player_position(t_game *game, int i, int j)
{
	game->player.x = j;
	game->player.y = i;
	if (game->map.map[i][j] == 'N')
		game->player.dir_x = 0;
	else if (game->map.map[i][j] == 'E')
		game->player.dir_x = 1;
	else if (game->map.map[i][j] == 'W')
		game->player.dir_x = 2;
	else if (game->map.map[i][j] == 'S')
		game->player.dir_x = 3;
	game->player.dir_y = 1;
}

// printf("Map : %c\n", game->map.map[i][j]);
// printf("Map : %s\n", game->map.map[i]);
// game->player.dir_y = 1; // TO DO : protection pour le retournement !!
int	is_player_valid(t_game *game)
{
	size_t	i;
	size_t	j;
	int		player;

	i = 0;
	player = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
				|| game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
			{
				set_up_player_position(game, i, j);
				player++;
			}
			j++;
		}
		i++;
	}
	if (is_player_here(player) == 1)
		return (1);
	return (0);
}

int	is_char_valid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0'
				&& game->map.map[i][j] != 'S' && game->map.map[i][j] != 'N'
				&& game->map.map[i][j] != 'W' && game->map.map[i][j] != 'E'
				&& game->map.map[i][j] != 32 && game->map.map[i][j] != '\0'
				&& game->map.map[i][j] != '\n')
			{
				printf("Invalid character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
