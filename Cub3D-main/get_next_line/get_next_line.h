/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:36:50 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/05 01:08:34 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_ist
{
	char			*content;
	struct s_ist	*next;
}				t_ist;

char	*get_next_line(int fd);
int		found_newline(t_ist *stash);
t_ist	*ft_lst_get_last(t_ist *stash);
void	read_and_stash(int fd, t_ist **stash);
void	extract_line(t_ist *stash, char **line);
void	generate_line(char **line, t_ist *stash);
void	clean_stash(t_ist **stash);
int		ft_strlen2(const char *str);
void	free_stash(t_ist *stash);
#endif
