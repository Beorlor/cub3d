/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:18:38 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/17 18:28:37 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	i;
	size_t	lens1;
	size_t	lentrim;

	i = 0;
	lens1 = ft_strlen(s1);
	if (s1 == NULL)
		return (ft_strdup(""));
	if (set == NULL)
		return (ft_strdup(s1));
	while (check_char(set, s1[i]))
		i++;
	if (i == lens1)
		return (ft_strdup(""));
	while (check_char(set, s1[lens1 - 1]))
		lens1--;
	lentrim = lens1 - i;
	dest = (char *)malloc(sizeof(char) * (lentrim + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, &s1[i], lentrim);
	dest[lentrim] = '\0';
	return (dest);
}
