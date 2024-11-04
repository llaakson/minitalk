/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:48:10 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/09 16:10:16 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	while (nb != 0)
	{
		nb /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char		*str;
	size_t		a;
	long int	l;

	l = nb;
	a = counter(l);
	if (nb < 0)
	{
		l *= -1;
		a++;
	}
	str = (char *)malloc(sizeof(char) * (a + 1));
	if (str == NULL)
		return (NULL);
	str[a] = '\0';
	while (--a)
	{
		str[a] = (l % 10 + '0');
		l = l / 10;
	}
	if (nb < 0)
		str[0] = '-';
	else
		str[0] = l + '0';
	return (str);
}
