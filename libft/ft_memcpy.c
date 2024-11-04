/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:16:56 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/10 22:56:43 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*char_dst;
	char	*char_src;

	char_dst = (char *) dst;
	char_src = (char *) src;
	if (src == NULL && dst == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}
