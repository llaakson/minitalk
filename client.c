/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/07 17:44:39 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

static int wait;

int	send_argument_size(char *argv, int id)
{
	int i;
	//char *lenstr; 
	int send = 32;
	int bit = 0;
	int wait_counter = 0;
	
	i = ft_strlen(argv);
	while (send--)
	{
		bit = (i >> send) & 1;
		if (bit == 0)
			kill(id,SIGUSR2);
		if (bit == 1)
			kill(id,SIGUSR1);
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
		printf("%d", bit);
	}
	printf("\n32 should have been send by now \n\n");
	//lenstr = ft_itoa(i); // check malloc fail
	//printf("n: %d s: %s\n",i,lenstr);
	//convert_binary(lenstr,id);
	return (0);
}

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
	send_argument_size(argv[2],id);
	write(1, "\n", 1);
	sleep(1);
	convert_binary(argv[2], id);
	return (0);
}
