/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:26:56 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/13 15:16:22 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tosearch;
	size_t	i;
	size_t	j;
	size_t	lens;

	i = -1;
	j = 0;
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	tosearch = (char *)malloc(sizeof(char) * (len + 1));
	if (!tosearch)
		return (NULL);
	while (s[++i])
	{
		if (i >= start && j < len)
		{
			tosearch[j] = s[i];
			j++;
		}
	}
	tosearch[j] = '\0';
	return (tosearch);
}
