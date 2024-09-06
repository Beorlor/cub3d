/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_textures_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:48:02 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 14:49:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	invalid_texture(t_game *game, char *line)
{
	printf("Invalid texture(s) - doublon\n");
	free(line);
	free(game->file);
	free_all2(game);
}

void	north_path(t_game *game, char *line)
{
	if (game->texture_paths[NORTH] == NULL)
		game->texture_paths[NORTH] = ft_strdup(line + 3);
	else
		invalid_texture(game, line);
}

void	south_path(t_game *game, char *line)
{
	if (game->texture_paths[SOUTH] == NULL)
		game->texture_paths[SOUTH] = ft_strdup(line + 3);
	else
		invalid_texture(game, line);
}

void	west_path(t_game *game, char *line)
{
	if (game->texture_paths[WEST] == NULL)
		game->texture_paths[WEST] = ft_strdup(line + 3);
	else
		invalid_texture(game, line);
}

void	east_path(t_game *game, char *line)
{
	if (game->texture_paths[EAST] == NULL)
		game->texture_paths[EAST] = ft_strdup(line + 3);
	else
		invalid_texture(game, line);
}
