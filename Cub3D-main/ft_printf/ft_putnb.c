/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:25:13 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/25 08:56:25 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_putnbr(unsigned int nb)
{
	if (nb >= 10)
	{
		ft_unsigned_putnbr(nb / 10);
		ft_unsigned_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
	return (count_unsigned_nb(nb, 10));
}

int	ft_putnb(int nb)
{
	int		i;

	i = count_nb(nb, 10);
	if (nb == -2147483648)
		ft_putstr("-2147483648");
	else if (nb < 0)
	{
		write(1, "-", 1);
		ft_putnb(-nb);
	}
	else if (nb > 9)
	{
		ft_putnb(nb / 10);
		ft_putnb(nb % 10);
	}
	else
		ft_putchar(nb + '0');
	return (i);
}

int	ft_putnb_hexa(unsigned int nb, char *base)
{
	int		i;
	char	tab[16];
	int		j;

	i = count_unsigned_nb(nb, 16);
	j = 0;
	while (nb != 0 || j == 0)
	{
		tab[j] = base[nb % 16];
		j++;
		nb = nb / 16;
	}
	while (j != 0)
		ft_putchar(tab[--j]);
	return (i);
}

int	ft_putnb_hexa_add(void *ptr, char *base)
{
	int					i;
	unsigned long int	nb;
	char				tab[16];
	int					j;

	if (!ptr)
		return (ft_putstr("(nil)"));
	nb = (unsigned long int)ptr;
	j = 0;
	i = count_unsigned_nb_add(nb, 16);
	while (nb != 0 || j == 0)
	{
		tab[j++] = base[nb % 16];
		nb = nb / 16;
	}
	i += ft_putstr("0x");
	while (j != 0)
		ft_putchar(tab[--j]);
	return (i);
}
