/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:10:39 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/13 14:56:40 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	array_counter(char const *s, char c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			i++;
		while (*str != c && *str)
			str++;
	}
	return (i);
}

static void	free_arr(char **arr, int i)
{
	while (0 < i)
	{
		i--;
		free(*(arr + i));
	}
	free(arr);
}

static char	**loop(char **arr, char const *s, char c)
{
	int	i;
	int	size;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			size = ft_strchr(s, c) - s;
			if (ft_strchr(s, c) == NULL)
				size = ft_strlen(s);
			arr[i] = ft_substr(s, 0, size);
			if (!*(arr + i))
			{
				free_arr(arr, i);
				return (NULL);
			}
			i++;
			s += size;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		j;

	if (!s)
		return (NULL);
	j = array_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * (j + 1));
	if (arr == NULL)
		return (NULL);
	arr = loop(arr, s, c);
	return (arr);
}
