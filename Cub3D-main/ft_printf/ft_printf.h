/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:22:31 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/25 08:56:25 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int				ft_putchar(char c);
int				ft_putstr(char *str);
int				count_nb(int n, int base);
int				count_unsigned_nb(unsigned int n, int base);
int				count_unsigned_nb_add(unsigned long int n, int base);
int				ft_unsigned_putnbr(unsigned int nb);
int				ft_putnb(int nb);
int				ft_putnb_hexa(unsigned int nb, char *base);
int				ft_putnb_hexa_add(void *ptr, char *base);
int				print_format(const char spe, va_list args);
int				ft_printf(const char *str, ...);

#endif
