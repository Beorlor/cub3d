/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:18:55 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/05 15:06:57 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bytepointer;
	unsigned char	bytevalue;

	i = 0;
	bytepointer = (unsigned char *)s;
	bytevalue = (unsigned char)c;
	while (i < n)
	{
		bytepointer[i] = bytevalue;
		i++;
	}
	return (bytepointer);
}
