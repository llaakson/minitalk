/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/06 20:45:41 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static int bit_counter;
static char print_bit;

void clean_bit()
{
	print_bit <<= 7;
}
void print_char()
{
	int i;
	char pr;

	i = 0;
	printf("\n%c\n",print_bit);
	bit_counter = 8;
	clean_bit();
}

void ft_print_signal(int signum, siginfo_t* info, void* context)
{
	(void)context;
	(void)info;
	(void)signum;
	if (signum == SIGUSR2)
	{
		write(1, "0", 2);
		print_bit <<= 1;
	}
	else if (signum == SIGUSR1)
	{
		write(1, "1", 2);
		print_bit = (print_bit << 1 ) | 1;
	}
	if (bit_counter == 0)
		print_char();
	bit_counter -= 1;
	kill(info->si_pid,SIGUSR2);
}

int main()
{
	struct sigaction siga;
	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	int pid;

	bit_counter = 7;
	print_bit = '9';
	clean_bit();
	pid = getpid();
	printf("%d\n",pid);	
	while(1)
	{
		sleep(1);
	}
	return (0);
}
