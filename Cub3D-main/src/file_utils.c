/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:54:57 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 15:55:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	open_file(const char *file, int fd, t_game *game)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	return (fd);
}

int	is_nb_of_rgb_good(int is_ceiling, int is_floor)
{
	if (is_ceiling == 2 || is_floor == 2)
		return (printf("There is a rgb id doublon\n"), 1);
	else if (is_ceiling > 2 || is_floor > 2)
		return (printf("Invalid rgb id\n"), 1);
	return (0);
}

int	ceiling(int is_ceiling, char c)
{
	if (c == 'C')
		is_ceiling++;
	return (is_ceiling);
}

int	if_floor(int is_floor, char c)
{
	if (c == 'F')
		is_floor++;
	return (is_floor);
}

void	init_type(int *floor, int *ceiling, int *fd)
{
	*floor = 0;
	*ceiling = 0;
	*fd = 1;
}
