/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/21 23:16:46 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	wait; //rename correctly

void	send_one_bit(int bit, int id)
{
	if (bit == 0)
	{
		kill(id, SIGUSR2);
		//write(1,"0",1);
	}
	if (bit == 1)
	{
		kill(id, SIGUSR1);
		//write(1,"1",1);
	}
	// check error
}

int send_one_byte(int pid, unsigned char byte)
{
	int i;
	int bit;

	i = 0;
	while (i < 8)
	{
		wait = 0;
		bit = byte >> (7 - i) & 1;
		send_one_bit(bit, pid);
		while (!wait)
		{
			usleep(100000);
			if(!wait)
			{
				write(2, "Time out\n", 9);
				return (0);
			}
		}
		i++;
	}
	//write(1,"\n", 1);
	return (0);
}
		
int	start_send(int pid, void *send, int size)
{
	int i;
	unsigned char *byte;

	byte = (unsigned char *)send;
	i = 0;
	while (i < size)
	{
		send_one_byte(pid,byte[i]);
		i++;
	}
	return (0);
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
	int	str_len;

	siga.sa_sigaction = ft_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	id = atoi(argv[1]);
	//wait = 0;
	if (argc != 3)
	{
		write(2, "Too many/few arguments\n", 23);
		exit (1);
	}
	sigaction(SIGUSR2, &siga, NULL);
	str_len = ft_strlen(argv[2]);
	start_send(id, &str_len, sizeof(str_len));
	start_send(id, argv[2], str_len);
	return (0);
}
