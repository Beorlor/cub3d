/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:19 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/05 18:11:50 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_everything(t_game *game)
{
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
	if (game->portal_gun.img)
		mlx_destroy_image(game->mlx, game->portal_gun.img);
	if (game->mini_map.img)
		mlx_destroy_image(game->mlx, game->mini_map.img);
	i = -1;
	while (++i < 2)
	{
		if (game->ball[i].texture.img)
			mlx_destroy_image(game->mlx, game->ball[i].texture.img);
		if (game->portals[i].texture.img)
			mlx_destroy_image(game->mlx, game->portals[i].texture.img);
	}
	i = -1;
	while (++i < 4)
	{
		if (game->texture_paths[i])
			free(game->texture_paths[i]);
	}
}

int	free_all2(t_game *game)
{
	int	i;

	mlx_do_key_autorepeaton(game->mlx);
	if (game->map.map)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.map[i] != NULL)
				free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
	}
	free_textures(game);
	free_everything(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	check_char(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
