/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:10:08 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/11 15:38:12 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		--i;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
