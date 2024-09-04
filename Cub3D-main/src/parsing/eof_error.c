/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:45:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 19:06:26 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	process_map(char *line, int fd, int map_ended)
{
	if (map_ended)
	{
		if (is_end_of_map(line, fd) == 1)
			return (-1);
	}
	else
	{
		map_ended = check_map(line, fd, map_ended);
		if (map_ended == -1)
			return (-1);
	}
	return (map_ended);
}

int	is_end_of_file(int map_started, int description)
{
	if (description == 0)
		return (printf("Map is not at the end of the file\n"), -1);
	map_started = 1;
	return (map_started);
}

void	init_var(int *fd, int *map_ended, int *description, int *map_started)
{
	*fd = 1;
	*map_ended = 0;
	*description = 0;
	*map_started = 0;
}

int	is_map_ended(char *line, int fd, int map_ended)
{
	map_ended = process_map(line, fd, map_ended);
	if (map_ended == -1)
		return (1);
	return (0);
}

int	end_of_file_loop(int map_ended, int description, int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!map_started)
		{
			if (is_description_line(line))
				description = 1;
			else if (check_map_line(line))
			{
				map_started = is_end_of_file(map_started, description);
				if (map_started == -1)
				{
					free(line);
					return (1);
				}
			}
		}
		else
			if (is_map_ended(line, fd, map_ended) == 1)
				return (free(line), 1);
		free (line);
	}
	return (0);
}

int	is_there_something_after_map(const char *file, t_game *game)
{
	int		fd;
	int		map_started;
	int		map_ended;
	int		description;

	(void)game;
	init_var(&fd, &map_ended, &description, &map_started);
	fd = open_file(file, fd);
	if (fd == -1)
		return (1);
	if (end_of_file_loop(map_ended, description, fd) == 1)
		return (close(fd), 1);
	close(fd);
	return (0);
}
