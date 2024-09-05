/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:25:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 10:40:28 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	are_file_textures_valid(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i] == NULL)
		{
			printf("Duplicate texture path\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// 	if (access(texture, X_OK) == -1)
// Maybe we must modify our paths to just get the real path (not NO).
int	are_paths_textures_valid(t_game *game)
{
	int		i;
	int		j;
	char	*texture;

	i = 0;
	while (game->texture_paths[i])
	{
		texture = game->texture_paths[i];
		j = 0;
		while (ft_isalpha(texture[j]) == 1 || texture[j] == 32)
			j++;
		texture += j;
		if (access(texture, X_OK) == -1)
		{
			printf("Texture path is wrong\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// fd = open_file(file, fd, game);
int	are_rgb_ids_valid(const char *file)
{
	int		fd;
	int		is_floor;
	int		is_ceiling;
	int		i;
	char	*line;

	init_type(&is_floor, &is_ceiling, &fd);
	fd = open_file(file, fd);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		i = -1;
		while (line[++i])
		{
			is_ceiling = ceiling(is_ceiling, line[i]);
			is_floor = if_floor(is_floor, line[i]);
		}
		free(line);
	}
	if (is_nb_of_rgb_good(is_ceiling, is_floor) == 1)
		return (1);
	return (0);
}

int	is_description_line(const char *line)
{
	return (strncmp(line, "NO ", 3) == 0
		|| strncmp(line, "SO ", 3) == 0
		|| strncmp(line, "WE ", 3) == 0
		|| strncmp(line, "EA ", 3) == 0
		|| strncmp(line, "F ", 2) == 0
		|| strncmp(line, "C ", 2) == 0);
}
