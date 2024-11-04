/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:22:39 by llaakson          #+#    #+#             */
/*   Updated: 2024/08/09 16:51:25 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_unsigned(int *ptr, unsigned int nb)
{
	if (nb >= 10)
	{
		ft_print_unsigned(ptr, nb / 10);
		ft_print_unsigned(ptr, nb % 10);
	}
	if (nb < 10)
		ft_putchar (ptr, nb + '0');
}

void	ft_putnbr(int *ptr, int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar(ptr, '-');
		ft_putchar(ptr, '2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar(ptr, '-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(ptr, nb / 10);
		ft_putnbr(ptr, nb % 10);
	}
	if (nb < 10)
		ft_putchar(ptr, nb + '0');
}

void	ft_putstr(int *ptr, char *s)
{
	int		i;
	char	*c;

	c = "(null)";
	i = 0;
	if (!s)
	{
		while (c[i] != '\0')
		{
			ft_putchar(ptr, c[i]);
			i++;
		}
		return ;
	}
	while (s[i] != '\0')
	{
		ft_putchar(ptr, s[i]);
		i++;
	}
}

void	ft_hexadecimal(int *ptr, unsigned int nb, const char *format)
{
	if (nb >= 16)
	{
		ft_hexadecimal(ptr, nb / 16, format);
		ft_hexadecimal(ptr, nb % 16, format);
	}
	if (nb < 10)
		ft_putchar(ptr, nb + 48);
	else if (nb < 16)
	{
		if (*format == 'x')
			ft_putchar(ptr, nb + 87);
		else
			ft_putchar(ptr, nb + 55);
	}
}
