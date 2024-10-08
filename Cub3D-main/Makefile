# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 18:59:35 by jeza              #+#    #+#              #
#    Updated: 2024/09/05 18:41:29 by jeguerin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = cub3D

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/ -Iminilibx -g

#Liste des fichiers source.
SRCS = src/main.c src/events.c src/init.c src/utils.c src/graphic/graphic.c \
       src/utils2.c src/init2.c src/move_player.c src/mini_map.c \
       src/parsing/eof_error.c src/parsing/fill_map.c src/parsing/map_errors.c \
       src/parsing/map_walls.c src/parsing/parser.c src/parsing/parser_description_file.c \
       src/parsing/valid_file.c src/parsing/file_errors.c src/parsing/file_utils.c \
	   src/parsing/map_utils.c src/sprites/portal_gun.c src/sprites/wall_textures.c \
	   src/parsing/set_up_direction.c src/parsing/set_up_textures_path.c \
	   src/parsing/map_door.c src/sprites/gun_shot.c src/parsing/portal_parsing.c \
	   src/manage_mouse.c src/init3.c src/draw_mini_map.c src/is_moving.c \
	   src/parsing/process_map.c src/teleport.c src/utils_teleport.c src/render.c \
	   src/sprites/manage_ball.c src/sprites/draw_ball.c src/sprites/ball_utils.c \
	   src/sprites/manage_portal.c src/graphic/graphic2.c src/graphic/graphic3.c \
	   src/graphic/graphic4.c src/graphic/graphic5.c \


LIBFT = Libft/libft.a
GETNEXTLINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
PRINTF = ft_printf/libftprintf.a
MINILIBX = minilibx/libmlx.a

LIBRARY:= -Lminilibx -lmlx -L/usr/X11R6/lib -lXext -lX11 -lbsd
OBJS = $(SRCS:.c=.o)
GETNEXTLINE_OBJ := $(GETNEXTLINE:.c=.o)

# Regle par defaut pour l'executable
all: author $(NAME)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Authors : jedurand & jeguerin\n"
	@echo "Project : Cub3D project\n"

$(LIBFT):
	make -C Libft

$(PRINTF):
	make -C ft_printf

$(MINILIBX):
	make -C minilibx

# Regle pour creer l'executable en liant les objets.
$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(GETNEXTLINE_OBJ) $(LIBFT) $(PRINTF) -o $(NAME) -lm

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS)
	$(RM) $(GETNEXTLINE_OBJ)
	make clean -C Libft
	make clean -C ft_printf
	make clean -C minilibx

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft
	make fclean -C ft_printf
	make clean -C minilibx

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re
