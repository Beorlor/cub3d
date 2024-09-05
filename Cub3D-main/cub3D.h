/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:50:25 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 12:50:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h> // perror - strerror
# include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
# include <sys/wait.h> // Wait
# include <fcntl.h>
# include <math.h> // cos - sin
# include <ctype.h>

# define KEY_ESC 65307
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_W 119 // OK
# define KEY_A 97 // OK
# define KEY_S 115 // OK
# define KEY_D 100 // OK
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define SZ 32
# define ON_DESTROY 17

# define M_SIZE 12 // Taille mini-map (en nb de tuiles)
# define T_SIZE 6 // Taille d'une tuile (en pixels)

# define MINIMAP_WIDTH 100
# define MINIMAP_HEIGHT 100

# define MOUSE_LEFT_CLICK 1

typedef enum s_texture_index
{
	NORTH = 0,
	EAST = 1,
	WEST = 2,
	SOUTH = 3
}	t_texture_index;

typedef enum s_keys_index
{
	W_INDEX = 0,
	A_INDEX = 1,
	S_INDEX = 2,
	D_INDEX = 3,
	LEFT_INDEX = 4,
	RIGHT_INDEX = 5,
	UP_INDEX = 6,
	DOWN_INDEX = 7
}	t_keys_index;

typedef struct s_input
{
	int	mouse_left_pressed;
	int	mouse_x;
	int	mouse_y;
	int	last_mouse_x;
	int	last_mouse_y;
}	t_input;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ball
{
	double		x;
	double		y;
	double		wx;
	double		wy;
	double		direction_x;
	double		direction_y;
	double		speed;
	int			stage;
	int			size;
	int			active;
	t_texture	texture;
}	t_ball;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_portal
{
	t_texture	texture;
	int			active;
	double		x;
	double		y;
	int			direction;
	int			link;
}	t_portal;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	speed;
	double	rot_speed;
}	t_player;

typedef struct s_render_vars
{
	int			ceiling_color;
	int			floor_color;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
	t_texture	*overlay_texture;
	int			x;
	int			y;
	int			walk_offset;
	int			mid_height;
	int			color;
	int			overlay_tex_x;
	int			overlay_tex_y;
	int			overlay_color;
}	t_render_vars;

typedef struct s_gun_vars
{
	double	x;
	double	y;
	double	center_x;
	double	center_y;
	double	dx;
	double	dy;
	double	distance;
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;
	int		direction;
	int		side;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		portal_index;
	int		tex_width;
	int		tex_height;
	double	scale_x;
	double	scale_y;
	int		start_x;
	int		start_y;
	int		tex_x;
	int		tex_y;
	int		color;
	int		screen_x;
	int		screen_y;
	int		current_portal_index;
	int		current_map_x;
	int		current_map_y;
	int		current_direction;
}	t_gun_vars;

typedef struct s_map_processing
{
	int	map_ended;
	int	description;
	int	map_started;
}	t_map_processing;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	int					win_height;
	int					win_width;
	t_map				map;
	t_player			player;
	t_texture			textures[4];
	t_color				floor;
	t_color				ceiling;
	t_input				input;
	t_texture			mini_map;
	t_texture			portal_gun;
	t_ball				ball[2];
	int					orientation;
	int					gun_shot;
	int					shot_frame;
	char				*texture_paths[4];
	int					running;
	int					touch_state[6];
	int					walk_offset;
	int					frame_count;
	t_portal			portals[2];
	int					skip_mouse_event;
	t_render_vars		render_vars;
	t_gun_vars			gun_vars;
	t_map_processing	mprocess;
	int					teleport_cooldown;
}	t_game;

// UTILS
int		free_all2(t_game *game);
void	free_everything(t_game *game);
void	free_textures(t_game *game);
int		ft_isspace(char *line);
int		check_char(char const *set, char c);
int		ft_atoi2(const char *nptr);
int		ft_strncmp_cub(const char *s1, char c, size_t n);
int		only_space(char *line);
int		check_map_line(char *line);
int		is_description_line(const char *line);
int		error(t_game *game, char *str);
int		open_file(const char *file, int fd);
void	draw_center_circle(t_game *game, int radius);
int		it_is_out(t_game *game, int x, int y);

// INITIALIZATION OF STRUCTURES
void	init_cub(t_game *game);
void	init_game(t_game *game);
void	init_texture(t_texture *texture);
void	init_color(t_color *color);
void	init_input(t_input *input);
void	create_window(t_game *game);
void	create_textures(t_game *game);
void	read_map(t_game *game, char *file);
void	malloc_map(t_game *game);
void	fill_map(t_game *game, char *file);
void	init_textures(t_game *game);
void	manage_errors(t_game *game, char *file);
void	init_ball(t_game	*game);
void	init_player(t_player *player);
void	init_map(t_map *map);
void	init_portals(t_game *game);

// MAP ERRORS
int		is_map_valid(t_game *game);
int		is_map_empty(t_game *game);
int		is_char_valid(t_game *game);
int		are_walls_valid(t_game *game);
char	**get_map(t_game *game);
int		flood_fill(t_game *game, char **map, int x, int y);
int		is_end_of_map(char *line, int fd);
int		is_player_valid(t_game *game);
void	manage_width(t_game *game, char *line);
void	am_i_going_to_far(t_game *game, char *line, int i);
void	increment_if_digit(char **line);
char	*error_line(char *line);
int		check_map(char *line, int fd, int map_ended);
int		is_door_valid(t_game *game);
void	set_up_north(t_game *game);
void	set_up_east(t_game *game);
void	set_up_west(t_game *game);
void	set_up_south(t_game *game);

// FILE ERRORS
int		is_file_valid(const char *file, t_game *game);
int		parse_rgb(char *line, int *r, int *g, int *b);
int		is_rgb_code(t_game *game, char *line);
void	invalid_rgb(char *line, t_game *game);
int		is_path_textures(t_game *game, char *line);
void	north_path(t_game *game, char *line);
void	south_path(t_game *game, char *line);
void	west_path(t_game *game, char *line);
void	east_path(t_game *game, char *line);
void	invalid_texture(t_game *game, char *line);
int		are_file_textures_valid(t_game *game);
int		is_file_full(const char *file, t_game *game);
int		are_paths_textures_valid(t_game *game);
int		are_rgb_ids_valid(const char *file);
int		process_map(char *line, int fd, int map_ended);
int		handle_description(char *line, int description);
int		is_file_extension_valid(const char *file);
int		is_file_empty(const char *file, t_game *game);
int		is_there_something_after_map(const char *file, t_game *game);
void	init_type(int *floor, int *ceiling, int *fd);
int		ceiling(int is_ceiling, char c);
int		if_floor(int is_floor, char c);
int		is_nb_of_rgb_good(int is_ceiling, int is_floor);
int		check_textures_and_rgb(t_game *game, char *line,
			int *textures, int *rgb);
int		check_nb_of_rgb_textures(int rgb, int textures);
void	init_ceiling_colors(t_game *game, int r, int g, int b);
void	init_floor_colors(t_game *game, int r, int g, int b);
int		are_textures_xpm(t_game *game);
void	load_portal_textures(t_game *game);

// EVENTS MANAGEMENT
int		mouse_move(int x, int y, t_input *input);
int		mouse_release(int button, int x, int y, t_input *input);
int		mouse_press(int button, int x, int y, t_input *input);
int		game_loop(t_game *game);
int		handle_input(t_game *game);
int		manage_keyrelease(int keycode, t_game *game);
int		manage_keypress(int keycode, t_game *game);
int		manage_mouse_click(int button, int x, int y, t_game *game);
void	is_action(t_game *game);
void	move_east_or_west(t_game *game, double *move_x,
			double *move_y, int *is_moving);
void	move_north_or_south(t_game *game, double *move_x,
			double *move_y, int *is_moving);
void	if_rotate(t_game *game);
void	moving(t_game *game, int is_moving, double move_x, double move_y);
void	try_move(t_game *game, double move_x, double move_y);

// PLAYER POSITION
void	update_position(t_game *game, double move_x, double move_y);
int		is_outside(t_game *game, double x, double y);
void	check_map_path(double x, double y, t_game *game);
void	rotate_player(t_game *game, double angle);
int		manage_mouse_movement(int x, int y, t_game *game);

// MANAGE MINI_MAP
void	render_mini_map(t_game *game, t_texture *frame);
void	draw_mini_map(t_game *game);
void	draw(t_texture *img, int x, int y, int color);
void	draw_player(t_game *game, t_texture *mini_map);
int		is_wall(t_game *game, double map_x, double map_y);
void	draw_view_direction(t_game *game, t_texture *mini_map);
void	my_mlx_pixel_put(t_texture *img, int x, int y, int color);
void	draw_mini_map_pixel(t_game *game, int y);
void	draw_mini_map_player(t_game *game);
void	draw_pixel(t_texture *img, int x, int y, int color);

// SPRITES - DISPLAY
int		display_each_frame(t_game *game);
void	load_portal_gun(t_game *game);
void	display_portal_gun(t_game *game, t_texture *frame);
void	create_ball(t_game *game, int button);
t_ball	*set_up_ball(t_game *game, int button);
void	update_balls(t_game *game);
void	move_ball_towards_center(t_game *game, t_ball *ball);
void	load_ball_textures(t_game *game);
void	draw_ball(t_game *game, t_texture *frame);
void	my_mlx_pixel_put(t_texture *img, int x, int y, int color);

// RENDERING FUNCTIONS
void	render_scene(t_game *game, t_texture *frame);
int		is_player_next_to_door(t_game *game, int map_x, int map_y);

#endif
