/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:26:11 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/13 14:15:41 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!len && !haystack)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0' && j < len)
	{
		while (haystack[j + i] == needle[i] && i + j < len)
		{
			if (needle[i + 1] == '\0')
				return ((char *)&haystack[j]);
			++i;
		}
		i = 0;
		++j;
	}
	return (NULL);
}
