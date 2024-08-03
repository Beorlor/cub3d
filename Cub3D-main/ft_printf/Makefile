
SRCS = ft_printf.c ft_print.c ft_putnb.c ft_count_nb.c


CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

OBJS = $(SRCS:.c=.o)

all :	${NAME}

${NAME} : $(OBJS)
		ar -rcs -o $(NAME) $(OBJS)


clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re
