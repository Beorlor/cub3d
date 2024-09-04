/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:24:13 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 16:30:18 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] <= 9 || line[i] >= 13 || line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}
// Exit useful ?

int	how_many_signs(const char *nptr, int sign, int i)
{
	if (nptr[i + 1] == 45 || nptr[i + 1] == 43)
		return (0);
	if (nptr[i] == 45)
		sign = -1;
	return (sign);
}

int	skip_spaces(const char *nptr, int i)
{
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi2(const char *nptr)
{
	int		i;
	int		sign;
	int		result;
	int		check;

	i = 0;
	sign = 1;
	result = 0;
	check = -1;
	i = skip_spaces(nptr, i);
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		sign = how_many_signs(nptr, sign, i);
		if (sign == 0)
			return (1);
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + (nptr[i++] - '0');
		check = 0;
	}
	if (check == -1)
		return (-1);
	return (result * sign);
}

int	ft_strncmp_cub(const char *s1, char c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == 32)
		i++;
	while ((unsigned char)s1[i] && ((unsigned char)s1[i]
			== (unsigned char)c) && (i < n - 1))
	{
		printf("Char : %c\n", s1[i]);
		i++;
	}
	if (i == n - 1)
	{
		printf("OK\n");
		return (0);
	}
	else
		return (1);
}
