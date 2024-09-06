/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:45:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 16:38:22 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int		process_map(char *line, int fd, int map_ended);
int		is_end_of_file(int map_started, int description);
void	init_map_processing(t_map_processing *mprocess);
int		is_map_ended(char *line, int fd, int map_ended);
int		handle_map_start(char *line, t_map_processing *mprocess);
int		process_line(char *line, int fd, t_map_processing *mprocess);
int		end_of_file_loop(int fd, t_map_processing *mprocess);

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

int	open_file2(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	process_line(char *line, int fd, t_map_processing *mprocess)
{
	if (!mprocess->map_started)
	{
		return (handle_map_start(line, mprocess));
	}
	else
	{
		if (is_map_ended(line, fd, mprocess->map_ended) == 1)
		{
			return (1);
		}
	}
	return (0);
}

int	end_of_file_loop(int fd, t_map_processing *mprocess)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (process_line(line, fd, mprocess) == 1)
		{
			free(line);
			line = get_next_line(fd);
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd);
			}
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
