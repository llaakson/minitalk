/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/27 11:53:39 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_wait;

static	void	send_one_bit(int bit, int id)
{
	if (bit == 0)
	{
		if (kill(id, SIGUSR2) == -1)
		{
			write(2, "Error sending signal\n", 21);
			exit (1);
		}
	}
	if (bit == 1)
	{
		if (kill(id, SIGUSR1) == -1)
		{
			write(2, "Error sending signal\n", 21);
			exit (1);
		}
	}
}

static int	send_one_byte(int pid, unsigned char byte)
{
	int	i;
	int	bit;
	int	wait_counter;

	wait_counter = 0;
	i = 0;
	while (i < 8)
	{
		g_wait = 0;
		bit = byte >> (7 - i) & 1;
		send_one_bit(bit, pid);
		while (!g_wait)
		{
			usleep(1000000);
			if (wait_counter == 50)
			{
				write(2, "Time out\n", 9);
				return (0);
			}
			wait_counter++;
		}
		wait_counter = 0;
		i++;
	}
	return (1);
}

int	start_send(int pid, void *send, int size)
{
	int				i;
	unsigned char	*byte;

	byte = (unsigned char *)send;
	i = 0;
	while (i < size)
	{
		if (!(send_one_byte(pid, byte[i])))
			return (1);
		i++;
	}
	return (0);
}

void	ft_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
	if (signum == SIGUSR2)
		g_wait = 1;
	if (signum == SIGUSR1)
	{
		write(2, "Server error\n", 13);
		exit (1);
	}
}

int	main(int argc, char **argv)
{
	int					id;
	struct sigaction	siga;

	if (argc != 3)
	{
		write(2, "Insert ./client PID STRING\n", 27);
		exit (1);
	}
	id = check_pid(argv[1]);
	siga.sa_sigaction = ft_signal;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	if (sigaction(SIGUSR2, &siga, NULL) == -1)
		exit(1);
	if (sigaction(SIGUSR1, &siga, NULL) == -1)
		exit(1);
	start_sending(argv[2], id);
	return (0);
}
