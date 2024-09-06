/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:32:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 16:38:26 by jeguerin         ###   ########.fr       */
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

int	is_map_ended(char *line, int fd, int map_ended)
{
	map_ended = process_map(line, fd, map_ended);
	if (map_ended == -1)
		return (1);
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

int	is_there_something_after_map(t_game *game)
{
	int	fd;

	init_map_processing(&game->mprocess);
	fd = open_file2(game->file);
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
