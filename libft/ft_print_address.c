/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:37:25 by llaakson          #+#    #+#             */
/*   Updated: 2024/08/09 16:50:40 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_address_affix(int *ptr, unsigned long long nb)
{
	ft_putchar(ptr, '0');
	ft_putchar(ptr, 'x');
	ft_print_address(ptr, nb);
}

void	ft_print_address(int *ptr, unsigned long long nb)
{
	if (nb >= 16)
	{
		ft_print_address(ptr, nb / 16);
		ft_print_address(ptr, nb % 16);
	}
	if (nb < 10)
		ft_putchar(ptr, (nb + 48));
	else if (nb < 16)
		ft_putchar(ptr, (nb + 87));
}
