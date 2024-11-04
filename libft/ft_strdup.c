/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:40:16 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/10 23:16:53 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*source;
	char	*destination;
	int		i;

	source = (char *)s1;
	destination = malloc (sizeof(char) * (ft_strlen(source) + 1));
	if (destination == NULL)
		return (NULL);
	i = 0;
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		++i;
	}
	destination[i] = '\0';
	return (destination);
}
