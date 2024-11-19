/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/18 15:47:20 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	wait; //rename correctly

void	send_one_bit(int bit, int id)
{
	if (bit == 0)
		kill(id, SIGUSR2);
	if (bit == 1)
		kill(id, SIGUSR1);
	// check error
}

int	send_argument_size(char *argv, int id)
{
	int	i;
	int	send;
	int	bit;
	int	wait_counter;

	wait_counter = 0;
	i = ft_strlen(argv);
	send = 8 * sizeof(i);
	while (send--)
	{
		bit = (i >> send) & 1;
		send_one_bit(bit, id);
		while (wait == 0)
		{	
			usleep(100000);
			if (wait_counter == 50)
			{
				write (1, "faiLL\n", 6);
				exit (1);
			}
			wait_counter++;
		}
		wait = 0;
		wait_counter = 0;
	}
	return (0);
}

int	convert_binary(char ch, int id)
{
	int	i;
	int	bit;
	int	wait_counter;

	i = 8;
	wait_counter = 0;
	while (i--)
	{
		bit = (ch >> i) & 1;
		send_one_bit(bit, id);
		while (wait == 0)
		{	
			usleep(100000);
			if (wait_counter == 50)
			{
				write (1, "fail\n", 5);
				exit (1);
			}
			wait_counter++;
		}
		wait = 0;
		wait_counter = 0;
	}
	return (0);
}

int	send_signal(char *argv, int id)
{
	char	ch;

	while (*argv)
	{	
		ch = argv[0];
		convert_binary(ch, id);
		argv++;
	}
	return (0);
}

void	send_null(int id)
{
	int	i;
	int	wait_counter;

	i = 8;
	wait_counter = 0;
	while (i--)
	{
		kill(id, SIGUSR2);
		while (wait == 0)
		{	
			usleep(100000);
			if (wait_counter == 50)
			{
				write (1, "fail\n", 5);
				exit (1);
			}
			wait_counter++;
		}
		wait = 0;
		wait_counter = 0;
	}
}

void ft_signal(int signum, siginfo_t* info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
	wait = 1;
}

int	main(int argc, char **argv)
{
	int					id;
	struct sigaction	siga;

	siga.sa_sigaction = ft_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	id = atoi(argv[1]);
	wait = 0;
	if (argc != 3)
	{
		write(2, "Too many/few arguments\n", 23);
		exit (1);
	}
	sigaction(SIGUSR2, &siga, NULL);
	send_argument_size(argv[2], id);
	sleep(1);
	send_signal(argv[2], id);
	send_null(id);
	return (0);
}
