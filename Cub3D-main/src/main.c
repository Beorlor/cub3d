/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:02:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:02:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	create_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				game->texture_paths[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Could not create mlx image\n");
			free_all2(game);
		}
		game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].pixel_bits, &game->textures[i].size_line,
				&game->textures[i].endian);
		i++;
	}
}

void	create_window(t_game *game)
{
	if (game->mlx == NULL)
	{
		printf("Mlx has not been set up\n");
		return ;
	}
	game->win = mlx_new_window(game->mlx, 800, 800,
			"Cub3d - A portail's world");
	if (!game->win)
	{
		printf("Could not create mlx window\n");
		return ;
	}
	mlx_mouse_hide(game->mlx, game->win);
	mlx_hook(game->win, 2, 1L << 0, manage_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, manage_keyrelease, game);
	mlx_hook(game->win, 4, 1L << 2, manage_mouse_click, game);
	mlx_hook(game->win, 17, KeyPressMask, free_all2, game);
	mlx_loop_hook(game->mlx, display_each_frame, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, manage_mouse_movement,
		game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop(game->mlx);
}

// Init structures
// Create map
// Check map errors
int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		return (printf("Wrong nb of arguments\n"), 1);
	memset(&game, 0, sizeof(t_game));
	game.file = ft_strdup(argv[1]);
	if (!game.file)
		return (printf("There is no map\n"), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (printf("Could not start mlx\n"), 1);
	init_cub(&game);
	read_map(&game);
	malloc_map(&game);
	fill_map(&game);
	manage_errors(&game);
	free(game.file);
	create_textures(&game);
	load_portal_textures(&game);
	memset(&game.render_vars, 0, sizeof(t_render_vars));
	memset(&game.gun_vars, 0, sizeof(t_gun_vars));
	memset(&game.mprocess, 0, sizeof(t_map_processing));
	create_window(&game);
	mlx_loop(game.mlx);
	return (free_all2(&game), 0);
}
