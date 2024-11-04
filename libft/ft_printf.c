/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:04:39 by llaakson          #+#    #+#             */
/*   Updated: 2024/08/09 16:51:06 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int *ptr, int c)
{
	int	temp;

	if (*ptr == -1)
		return ;
	temp = write (1, &c, 1);
	if (temp < 0)
	{
		*ptr = -1;
		return ;
	}
	*ptr += temp;
}

void	ft_format(int *ptr, va_list arguments, const char *format)
{
	if (*format == 's')
		ft_putstr(ptr, va_arg(arguments, char *));
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(ptr, va_arg(arguments, int));
	else if (*format == 'c')
		ft_putchar(ptr, va_arg(arguments, int));
	else if (*format == '%')
		ft_putchar(ptr, '%');
	else if (*format == 'p')
		ft_address_affix(ptr, va_arg(arguments, unsigned long long));
	else if (*format == 'X' || *format == 'x')
		ft_hexadecimal(ptr, va_arg(arguments, unsigned int), format);
	else if (*format == 'u')
		ft_print_unsigned(ptr, va_arg(arguments, unsigned int));
	else
		ft_putchar(ptr, *format);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		counter;
	int		*ptr;

	va_start (arguments, format);
	counter = 0;
	ptr = &counter;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break ;
			ft_format(ptr, arguments, format);
			format++;
		}
		if (*format && *format != '%')
		{
			ft_putchar(ptr, *format);
			format++;
		}
	}
	va_end (arguments);
	return (counter);
}
