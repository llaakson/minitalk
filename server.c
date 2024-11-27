/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:09 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/27 11:26:01 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"

static int	g_signal;

static int	ft_get_bit(unsigned char *bit)
{
	int	i;
	int	wait_counter;

	wait_counter = 0;
	i = 0;
	while (8 > i)
	{
		while (!g_signal)
		{
			usleep(1000000);
			if (wait_counter == 50)
				return (0);
			wait_counter++;
		}
		wait_counter = 0;
		if (g_signal == SIGUSR1)
			*bit |= 1 << (7 - i);
		i++;
		g_signal = 0;
		if (kill(set_pid(-1), SIGUSR2) == -1)
			write(2, "Error sending signal\n", 21);
	}
	return (1);
}

static bool	ft_message_length(void *str_size, int counter)
{
	unsigned char	*temp;
	int				i;

	ft_bzero(str_size, counter);
	temp = (unsigned char *)str_size;
	i = 0;
	while (i < counter)
	{
		if (!(ft_get_bit(&temp[i])))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_print_message(int str_size)
{
	char	*str;

	str = malloc(str_size + 1);
	if (!str)
	{
		write(2, "Failed to allocate memory\n", 26);
		return ;
	}
	if (ft_message_length(str, str_size) == false)
	{
		free(str);
		str = NULL;
		write(2, "Signal lost\n", 12);
		if (kill(set_pid(-1), SIGUSR1) == -1)
			write(2, "Error sending signal\n", 21);
		return ;
	}
	str[str_size] = '\0';
	ft_printf("%s\n", str);
	free (str);
	str = NULL;
}

void	ft_signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (!(set_pid(info->si_pid)))
		g_signal = signum;
}

int	main(void)
{
	struct sigaction	siga;
	int					str_size;
	bool				str_size_ptr;

	siga.sa_sigaction = ft_signal_handler;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	if ((sigaction(SIGUSR1, &siga, NULL) == -1))
		exit(1);
	if ((sigaction(SIGUSR2, &siga, NULL) == -1))
		exit(1);
	ft_printf("%d\n", getpid());
	while (1)
	{
		set_pid(0);
		str_size = 0;
		str_size_ptr = ft_message_length(&str_size, sizeof(int));
		if (str_size_ptr == true && str_size > 0)
			ft_print_message(str_size);
	}
	return (0);
}
