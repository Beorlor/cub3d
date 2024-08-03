/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:36:12 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 15:38:24 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	manage_width(t_game *game, char *line)
{
	int	line_length;

	line_length = 0;
	line_length = ft_strlen(line);
	if (line[line_length - 1] == '\n')
		line_length--;
	if (line_length > game->map.width)
		game->map.width = line_length;
	game->map.height++;
}

int	error(t_game *game, char *str)
{
	while (*str)
		write(2, str++, 1);
	free_all2(game);
	return (1);
}

char	*error_line(char *line)
{
	if (*line == ',')
		return (line + 1);
	else
		return (NULL);
}

void	increment_if_digit(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
}

void	am_i_going_to_far(t_game *game, char *line, int i)
{
	if (i >= game->map.height)
	{
		printf("Error: map height exceeded allocated space\n");
		free(line);
		free_all2(game);
	}
}
