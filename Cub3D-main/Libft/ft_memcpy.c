/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:21:46 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/13 13:38:53 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy( void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*bytedest;
	const unsigned char	*bytesrc;

	i = 0;
	bytedest = (unsigned char *)dest;
	bytesrc = (const unsigned char *)src;
	if (dest == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		bytedest[i] = bytesrc[i];
		i++;
	}
	return ((unsigned char *)bytedest);
}
