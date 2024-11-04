/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:40:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/07/24 12:33:34 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static	void	ft_remain(char **remain)
{
	int		j;
	char	*new_remain;

	j = 0;
	while ((*remain)[j] && (*remain)[j] != '\n')
		j++;
	if ((*remain)[j] == '\n')
		j++;
	new_remain = ft_strdup(*remain + j);
	free (*remain);
	*remain = new_remain;
}

static	char	*ft_get_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, buffer, i);
	str[i] = '\0';
	return (str);
}

static	char	*ft_read(int fd, char *buffer, char *remain)
{
	int		sz;
	char	*temp_buffer;

	sz = 1;
	while (sz)
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz == -1)
		{
			free(buffer);
			return (ft_free(&remain));
		}
		buffer[sz] = '\0';
		temp_buffer = remain;
		remain = ft_strjoin_gnl(remain, buffer);
		if (!remain)
		{
			free (buffer);
			return (ft_free(&temp_buffer));
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (remain);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*remain;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(&remain));
	remain = ft_read(fd, buffer, remain);
	if (!remain)
		return (NULL);
	ret = ft_get_line(remain);
	if (!ret)
		return (ft_free(&remain));
	ft_remain(&remain);
	return (ret);
}
