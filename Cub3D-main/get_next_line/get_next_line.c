/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:35:18 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/06 10:37:57 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "get_next_line.h"

char	*update_stash(char *stash)
{
	int		i;
	char	*next_line;
	int		len;

	next_line = 0;
	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
	{
		i++;
		len = ft_strlen_gnl(stash + i);
		next_line = ft_strndup_gnl(stash + i, len);
	}
	else
		next_line = ft_strndup_gnl(stash + i, ft_strlen_gnl(stash + i));
	free(stash);
	return (next_line);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	if (ft_strchr_gnl(stash, '\n') == 1)
	{
		while (stash[i] != '\n' && stash[i])
			i++;
		if (stash[i] == '\n')
			i++;
	}
	else
		i = ft_strlen_gnl(stash);
	line = ft_strndup_gnl(stash, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			rd;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free(stash), stash = NULL, NULL);
	rd = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (rd != 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		buffer[rd] = '\0';
		stash = ft_join(stash, buffer);
		if (ft_strchr_gnl(stash, '\n') == 1)
			break ;
	}
	free(buffer);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return 0;
// }
