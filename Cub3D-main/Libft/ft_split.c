/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:42:20 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/17 18:28:37 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t	ft_countwords(char *str, char c)
{
	int		i;
	size_t	countw;

	i = 0;
	countw = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			countw++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (countw);
}

static char	**malloc_tab(const char *s, char c)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (ft_countwords((char *)s, c) + 1));
	if (new == NULL)
		return (NULL);
	return (new);
}

static void	extra(char const *s, int *i, int *j, char c)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	*j = *i;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	**new;

	i = 0;
	word = -1;
	new = malloc_tab(s, c);
	if (!new)
		return (NULL);
	while (s[i])
	{
		extra(s, &i, &j, c);
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			new[++word] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!new[word])
				return (NULL);
			ft_strncpy(new[word], &s[j], i - j);
		}
	}
	new[word + 1] = NULL;
	return (new);
}
