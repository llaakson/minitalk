/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/07 21:27:59 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static int bit_counter;
static char print_bit;

static char *print_str;

static int int_count;
static int str_size;


void clean_bit()
{
	print_bit <<= 7;
}
void print_char()
{	
	static int check = 1;
	if (check == 1)
	{
		printf("\nSIZE %d\n", str_size);
		print_str = malloc(sizeof(char)*str_size);
		check = 0;
	}

	static int i = 0;
	//printf("\n%c\n",print_bit);
	print_str[i++] = print_bit;
	printf("\n!!!! %s !!!!\n", print_str); 
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
		//write(1, "0", 2);
		if (int_count++ < 32)
			str_size <<= 1;
		print_bit <<= 1;
	}
	else if (signum == SIGUSR1)
	{
		//write(1, "1", 2);
		if (int_count++ < 32)
			str_size = (str_size << 1 ) | 1;
		print_bit = (print_bit << 1 ) | 1;
	}
	if (int_count > 32)
	{
		if (bit_counter == 0)
			print_char();
		bit_counter -= 1;
	}
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
	
	int_count = 0;
	str_size = 0;
	//print_str = NULL;

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
