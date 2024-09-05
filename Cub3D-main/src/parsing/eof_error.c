/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:45:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 10:57:55 by jedurand         ###   ########.fr       */
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

int	open_file2(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	is_there_something_after_map(const char *file, t_game *game)
{
	int	fd;

	init_map_processing(&game->mprocess);
	fd = open_file2(file);
	if (fd == -1)
		return (1);
	if (end_of_file_loop(fd, &game->mprocess) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	init_map_processing(t_map_processing *mprocess)
{
	mprocess->map_ended = 0;
	mprocess->description = 0;
	mprocess->map_started = 0;
}

int	handle_map_start(char *line, t_map_processing *mprocess)
{
	if (is_description_line(line))
	{
		mprocess->description = 1;
	}
	else if (check_map_line(line))
	{
		mprocess->map_started = is_end_of_file(mprocess->map_started,
				mprocess->description);
		if (mprocess->map_started == -1)
		{
			return (1);
		}
	}
	return (0);
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
