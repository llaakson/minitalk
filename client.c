/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/05 19:03:58 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int wait;

int convert_binary(char *argv, int id)
{
	int i;
	int bit;
	//int j = 0;
	int c;
	int wait_counter = 0;
	char ch = argv[0];
	c = 0; 
	i = 8;  //8 * strlen(argv);
	while (*argv)
	{		
		while (i--)
		{
			bit = (ch >> i) & 1;
			if (bit == 0)
				kill(id,SIGUSR2);
			if (bit == 1)
				kill(id,SIGUSR1);
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
			printf("%d", bit);
		}
		argv++;
		ch = argv[0];
		i = 8;
	}
	return(0);
}

void ft_signal(int signum, siginfo_t* info, void* context)
{
	(void)context;
	(void)info;
	(void)signum;
	wait = 1;
	//write(1, "aaa\n", 4);
}

int	main(int argc, char **argv)
{
	int id = atoi(argv[1]);
	struct sigaction siga;
	siga.sa_sigaction = ft_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;

	wait = 0;
	(void)argc;
	sigaction(SIGUSR2, &siga, NULL);
	convert_binary(argv[2], id);
	return (0);
}
