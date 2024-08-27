/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:37:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/27 19:43:07 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void    load_portal_gun(t_game *game)
{
    game->portal_gun.width = 64;
	game->portal_gun.height = 64;
	game->portal_gun.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/portal_gun.xpm", &game->portal_gun.width, &game->portal_gun.height);
    if (!game->portal_gun.img)
    {
		printf("Failed to load portal gun texture\n");
		free_all2(game);
    }
	game->portal_gun.addr = (int *)mlx_get_data_addr(game->portal_gun.img, &game->portal_gun.pixel_bits, &game->portal_gun.size_line, &game->portal_gun.endian);
	if (!game->portal_gun.addr)
    {
		printf("Failed to load portal gun address\n");
		mlx_destroy_image(game->mlx, game->portal_gun.img);
		free_all2(game);
    }
}

void	display_portal_gun(t_game *game)
{
	int	x;
	int	y;

	 if (!game->portal_gun.img) // Vérifiez si l'image est valide
    {
        printf("Portal gun image is not loaded.\n");
        return;
    }
	x = (game->win_width - game->portal_gun.width) / 2;
	y = game->win_height - game->portal_gun.height - 10; // 20 px au-dessus du bas de l'écran.
	if (game->gun_shot == 1) // Simuler le recul lors du tire avec l'arme.
	{
		y += 10;
		game->shot_frame++;
		if (game->shot_frame > 5) // Limiter la durée de l'animation.
		{
			game->gun_shot = 0;
			game->shot_frame = 0;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->portal_gun.img, x, y);
 }

 /*
 La boule doit avoir des coordonnees (pour calculer la distance avec le joueur, ajuster la taille de la boule)
 et une direction
 Boule sur le portal gun et quiva vers le centre de l'ecran.
 Clic gauche => Boule orange apparait / Clic droit => Boule bleue qui apparait
 => Part vers le centre de l'ecran a l'infini tant qu'on ne redemarre pas le programme.
 Prendre en compte la taille de la boule selon la distance  => Later

 */

void create_ball(t_game *game, int button)
{
    t_ball *ball;
	double	center_x;
	double	center_y;
	double	dx;
	double	dy;
	double	distance;

	ball = NULL;
    if (button == 1) // Clic gauche -> boule orange
        ball = &game->ball[0];
    else if (button == 3) // Clic droit -> boule bleue
        ball = &game->ball[1];
    else
	{
        return;
	}

	if (ball && !ball->active)
	{
		// Initialisation de la position et de la direction
		ball->x = game->player.x;
		ball->y = game->player.y;

		center_x = game->map.width / 2.0;
		center_y = game->map.height / 2.0;
		dx = center_x - ball->x;
		dy = center_y - ball->y;
		distance = sqrt(dx * dx + dy * dy);

		ball->direction_x = (dx / distance) * 0.1;
		ball->direction_y = (dy / distance) * 0.1;

		ball->active = 1;
	}
}

void	load_ball_textures(t_game *game)
{
	game->ball[0].texture.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/orange_ball.xpm", &game->ball[0].texture.width, &game->ball[0].texture.height);
    if (!game->ball[0].texture.img)
    {
        printf("Failed to load orange ball texture\n");
        free_all2(game);
    }
    game->ball[0].texture.addr = (int *)mlx_get_data_addr(game->ball[0].texture.img, &game->ball[0].texture.pixel_bits, &game->ball[0].texture.size_line, &game->ball[0].texture.endian);

    game->ball[1].texture.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/blue_ball2.xpm", &game->ball[1].texture.width, &game->ball[1].texture.height);
    if (!game->ball[1].texture.img)
    {
        printf("Failed to load blue ball texture\n");
        free_all2(game);
    }
    game->ball[1].texture.addr = (int *)mlx_get_data_addr(game->ball[1].texture.img, &game->ball[1].texture.pixel_bits, &game->ball[1].texture.size_line, &game->ball[1].texture.endian);
}

void update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
    {
        if (game->ball[i].active)
        {
            // game->ball[i].x += game->ball[i].direction_x;
            // game->ball[i].y += game->ball[i].direction_y;
			move_ball_towards_center(game, &game->ball[i]);
            if (game->ball[i].x < 0 || game->ball[i].x >= game->win_width ||
                game->ball[i].y < 0 || game->ball[i].y >= game->win_height)
            {
                game->ball[i].active = 0;
            }
        }
		i++;
    }
}




void move_ball_towards_center(t_game *game, t_ball *ball)
{
    // Coordonnées du centre de la carte
    double center_x = game->map.width / 2.0;
    double center_y = game->map.height / 2.0;

    if (ball->active)
    {
        // Calculer la direction vers le centre
        double dx = center_x - ball->x;
        double dy = center_y - ball->y;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance > 1.0) // Continue à bouger si la distance au centre est significative
        {
            ball->x += ball->direction_x;
            ball->y += ball->direction_y;
        }
        else
        {
            // Fixe la boule au centre
            ball->x = center_x;
            ball->y = center_y;
            ball->direction_x = 0;
            ball->direction_y = 0;
        }
    }
}

void draw_ball(t_game *game)
{
	int	i;

	i = 0;
	while ( i < 2)
    {
        if (game->ball[i].active)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->ball[i].texture.img, game->ball[i].x, game->ball[i].y);
        }
		i++;
    }
}

