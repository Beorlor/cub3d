/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:56:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	are_textures_xpm(t_game *game)
{
	int	xpm_size;
	int	start_position;
	int	path_size;
	int	i;

	xpm_size = ft_strlen(".xpm");
	i = 0;
	while (i < 4)
	{
		path_size = ft_strlen(game->texture_paths[i]);
		start_position = path_size - xpm_size;
		if (start_position < 0
			|| ft_strcmp(game->texture_paths[i] + start_position, ".xpm") != 0)
			return (printf("Not a .xpm file: %s\n", game->texture_paths[i]), 1);
		i++;
	}
	return (0);
}

int	is_file_valid(t_game *game)
{
	if (is_file_extension_valid(game) == 1)
		return (1);
	if (is_file_empty(game) == 1)
		return (1);
	if (are_file_textures_valid(game) == 1)
		return (1);
	if (are_rgb_ids_valid(game) == 1)
		return (1);
	if (is_there_something_after_map(game) == 1)
		return (1);
	if (are_textures_xpm(game) == 1)
		return (1);
	return (0);
}
// if (is_there_one_map(file) == 1)
	// 	return (1);
// Texture paths : What's a valid path ???

int	is_map_valid(t_game *game)
{
	if (is_map_empty(game) == 1)
		return (1);
	if (is_char_valid(game) == 1)
		return (1);
	if (is_player_valid(game) == 1)
		return (1);
	if (are_walls_valid(game) == 1)
		return (1);
	if (is_door_valid(game) == 1)
		return (1);
	return (0);
}

void	manage_errors(t_game *game)
{
	if (is_file_valid(game) == 1)
	{
		free(game->file);
		free_all2(game);
	}
	if (is_map_valid(game) == 1)
	{
		free(game->file);
		free_all2(game);
	}
}

int	check_nb_of_rgb_textures(int rgb, int textures)
{
	if (rgb != 2 || textures != 4)
		return (printf("Map description is either wrong or incomplete\n"), 1);
	return (0);
}
