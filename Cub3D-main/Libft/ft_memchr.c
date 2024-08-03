/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:47:25 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/05 09:53:02 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*blocmem;
	unsigned char		searchval;
	size_t				i;

	blocmem = (const unsigned char *)s;
	searchval = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (blocmem[i] == searchval)
		{
			return ((unsigned char *)blocmem + i);
		}
		i++;
	}
	return (NULL);
}
