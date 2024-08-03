/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:22:31 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/07 11:07:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		ft_strlen_gnl(char *str);
int		ft_strchr_gnl(const char *str, int c);
char	*ft_strndup_gnl(const char *str, int size);
char	*ft_join(char *s1, char *s2);
char	*update_stash(char *stash);
char	*extract_line(char *stash);
void	*ft_calloc(size_t nmemb, size_t size);
void	free_all(void);
void	*malloc(size_t size);
void	free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);

#endif
