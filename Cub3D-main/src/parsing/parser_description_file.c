/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_description_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:39:43 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 13:25:22 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

// Test if line is well incremented when digit
int	parse_rgb(char *line, int *r, int *g, int *b)
{
	*r = ft_atoi2(line);
	if (*r == -1)
		return (printf("Red color code is missing\n"), 1);
	increment_if_digit(&line);
	line = error_line(line);
	if (line == NULL)
		return (1);
	*g = ft_atoi2(line);
	if (*g == -1)
		return (printf("Green color code is missing\n"), 1);
	increment_if_digit(&line);
	line = error_line(line);
	if (line == NULL)
		return (1);
	*b = ft_atoi2(line);
	if (*b == -1)
		return (printf("Blue color code is missing\n"), 1);
	increment_if_digit(&line);
	if (*line != '\0' && *line != '\n')
		return (1);
	if ((*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		&& ft_isspace(line) != 1)
		return (1);
	return (0);
}

void	invalid_rgb(char *line, t_game *game)
{
	printf("Invalid id for RGB color\n");
	free(line);
	free(game->file);
	free_all2(game);
}

int	is_rgb_code(t_game *game, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*rgb_line;

	if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
	{
		rgb_line = line + 2;
		if (parse_rgb(rgb_line, &r, &g, &b) == 1)
			invalid_rgb(line, game);
		if (line[0] == 'F')
			init_floor_colors(game, r, g, b);
		else if (line[0] == 'C')
			init_ceiling_colors(game, r, g, b);
		return (0);
	}
	else if (check_char(line, 32) != 1 && check_char(line, '\n') != 1)
		invalid_rgb(line, game);
	return (1);
}

int	is_path_textures(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && line[2] == ' ')
		north_path(game, line);
	else if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
		south_path(game, line);
	else if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
		west_path(game, line);
	else if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
		east_path(game, line);
	else
		return (1);
	return (0);
}

int	check_textures_and_rgb(t_game *game, char *line, int *textures, int *rgb)
{
	if (is_path_textures(game, line) == 0)
	{
		*textures += 1;
		return (1);
	}
	else if (*rgb != 2 && is_rgb_code(game, line) == 0)
	{
		*rgb += 1;
		return (1);
	}
	return (0);
}
