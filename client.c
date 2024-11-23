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

static int	g_wait;

void	send_one_bit(int bit, int id)
{
	if (bit == 0)
		if(kill(id, SIGUSR2) == -1)
		{
			write(2, "Sending signal failed\n", 22);
			exit(1);
		}
	if (bit == 1)
		if(kill(id, SIGUSR2) == -1)
                {
                        write(2, "Sending signal failed\n", 22);
                        exit(1);
                }
}

int send_one_byte(int pid, unsigned char byte)
{
	int i;
	int bit;

	i = 0;
	while (i < 8)
	{
		g_wait = 0;
		bit = byte >> (7 - i) & 1;
		send_one_bit(bit, pid);
		while (!g_wait)
		{
			usleep(100000);
			if(!g_wait)
			{
				write(2, "Time out\n", 9);
				return (1);
			}
		}
		i++;
	}
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
		if(!(send_one_byte(pid,byte[i])))
			return (1);
		i++;
	}
	return (0);
}

void ft_signal(int signum, siginfo_t* info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
	g_wait = 1;
}

int	main(int argc, char **argv)
{
	int					id;
	struct sigaction	siga;
	int	str_len;

	if (argc != 3)
        {
                write(2, "Too many/few arguments\n", 23);
                exit (1);
        }
	id = atoi(argv[1]);
	if (id >= 0)
	{
		write(2, "Negative pid\n", 13);
		exit (1);
	}
	siga.sa_sigaction = ft_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR2, &siga, NULL);
	str_len = ft_strlen(argv[2]);
	if(!(start_send(id, &str_len, sizeof(str_len))))
		exit(1);
	if(!(start_send(id, argv[2], str_len)))
		exit(1);
	return (0);
}
