/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/05 17:43:50 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void ft_print_signal(int signum, siginfo_t* info, void* context)
{
	(void)context;
	(void)info;
	(void)signum;
	if (signum == SIGUSR2)
		write(1, "0", 2);
	else if (signum == SIGUSR1)
		write(1, "1", 2);
	/*if (bit == 30)
		printf("signal %d\n", 0);
	if (bit == 17)
		printf("signal %d\n", 1);*/
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
	pid = getpid();
	printf("%d\n",pid);	
	while(1)
	{
		sleep(1);
	}
	return (0);
}
