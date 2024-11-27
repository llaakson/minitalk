/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:13:05 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/27 11:55:42 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	start_sending(char *str, int id)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str_len == 0)
	{
		write(2, "Message is empty\n", 17);
		exit(1);
	}
	if (start_send(id, &str_len, sizeof(str_len)))
		exit(1);
	if (start_send(id, str, str_len))
		exit(1);
}

int	check_pid(char *str)
{
	int	i;
	int	id;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
		{
			write(2, "Not a valid PID\n", 16);
			exit (1);
		}
		i++;
	}
	id = atoi(str);
	if (id <= 1)
	{
		write(2, "Not a valid PID\n", 16);
		exit (1);
	}
	return (id);
}
