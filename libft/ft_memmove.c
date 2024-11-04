/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:56:13 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/10 22:58:29 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*destination;

	destination = (char *) dst;
	source = (char *) src;
	i = len;
	if (len == 0)
		return (dst);
	if (destination == source)
		return (dst);
	if (source < destination)
	{
		while (len--)
			destination[len] = source[len];
	}
	else
	{
		while (i--)
			*destination++ = *source++;
	}
	return (dst);
}
