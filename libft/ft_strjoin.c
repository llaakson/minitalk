/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:33:39 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/13 15:09:00 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_string[j] = s1[i];
		++i;
		++j;
	}
	while (*s2)
	{
		new_string[j] = *s2;
		s2++;
		++j;
	}
	new_string[j] = '\0';
	return (new_string);
}
