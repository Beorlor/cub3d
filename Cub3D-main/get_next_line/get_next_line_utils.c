/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:35:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/06 10:37:49 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (-1);
}

char	*ft_strndup_gnl(const char *str, int size)
{
	char	*dest;
	int		i;

	i = 0;
	if (!str || size == 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_join(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;
	size_t	lens;

	i = 0;
	j = 0;
	lens = ft_strlen_gnl(s2);
	if (!s1)
		return (ft_strndup_gnl(s2, lens));
	lens = lens + ft_strlen_gnl(s1);
	dest = (char *)malloc(sizeof(char) * (lens + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

/*
fd = le descripteur de fichier a partir duquel on veut lire.
Ref. qui pointe vers un fichier.
buffer = un pointeur vers la zone de mem. ou les donnees lues seront stockees
count = le nb maximum d'octets a lire.
La fonction read essaie de lire count octets à partir du descripteur de
fichier fd et stocke ces octets dans la zone de mémoire pointée par buf.
*/

/*
Fonctions :
- strchr : Check le caractere nul
- Qui extrait de stash la ligne qu'on souhaite afficher
pour l'afficher (extract_line)
- Une fonction qui nettoie (MAJ)stash ? Update_stash
- Join : Dans le cas ou on n'a pas de \n il faut copier la static et
buffer dans une str,
(car sera ecrasee quand on remettra le new buffer)
Du coup, on va join que si on pas de \n dans la static et faudra clean une fois
qu'on a trouve le \n.
- Strndup : static = buffer_size
Malloc le buffer dans get_next_line.

Tu mets le buffer dans ta static, seulement s'il n'y a plus rien dedans.
Tu joins uniquement lorsque tu ne trouves pas de /n.
*/
