/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:26 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:55 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	is_file_extension_valid(const char *file)
{
	int	start_position;
	int	extension;
	int	size;

	size = ft_strlen(file);
	extension = ft_strlen(".cub");
	start_position = size - extension;
	if (start_position < 0 || ft_strcmp(file + start_position, ".cub") != 0)
	{
		printf("Not a .cub file\n");
		return (1);
	}
	return (0);
}

int	is_file_empty(const char *file, t_game *game)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	if (read(fd, &c, 1) == 0)
	{
		printf("File is empty\n");
		close(fd);
		free_all2(game);
	}
	close(fd);
	return (0);
}

/*
Check si une ligne vide puis wall puis wall puis vide et si apres pas bon !
*/
int	is_file_full(const char *file, t_game *game)
{
	int		fd;
	int		check;
	char	*line;

	check = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp_cub(line, '1', ft_strlen(line)) == 0)
			check++;
		if (check == 2 && line != NULL && *line != '\n')
		{
			printf("Map is not the last element in file\n");
			return (1);
		}
	}
	return (0);
}

int	is_end_of_map(char *line, int fd)
{
	(void)fd;
	if (!only_space(line))
	{
		printf("Map is not the last element in file\n");
		return (1);
	}
	return (0);
}

int	check_map(char *line, int fd, int map_ended)
{
	(void)fd;
	if (only_space(line))
		map_ended = 1;
	else if (!check_map_line(line))
	{
		printf("Invalid character found in map\n");
		return (-1);
	}
	return (map_ended);
}

// int	handle_map_line(char *line, int description)
// {
// 	if (check_map_line(line))
// 	{
// 		if (description == 0)
// 		{
// 			printf("Map is not at the end of the file\n");
// 			// free(line);
// 			printf("KO\n");
// 			return (1);
// 		}
// 		return (2);
// 	}
// 	return (0);
// }
