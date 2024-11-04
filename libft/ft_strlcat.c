/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:07 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/14 14:15:21 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	r;
	size_t	s;
	char	*src1;

	src1 = (char *)src;
	s = ft_strlen(src);
	if (!dst && !dstsize)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	if (dstsize > i)
		r = ft_strlen(dst) + ft_strlen(src);
	else
		r = dstsize + ft_strlen(src);
	j = 0;
	while ((src1[j] != '\0' && dstsize > i + 1))
	{
		dst[i] = src1[j];
		++j;
		++i;
	}
	dst[i] = '\0';
	return (r);
}
