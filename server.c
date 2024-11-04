/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/04 18:13:18 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void ft_print_signal(int bit)
{
	if (bit == 30)
		printf("signal %d\n", 0);
	if (bit == 17)
		printf("signal %d\n", 1);
}

int main()
{
	int pid;
	pid = getpid();
	printf("%d\n",pid);	
	while(1)
	{
		signal(30,ft_print_signal);
		signal(17,ft_print_signal);
		usleep(1);
	}
	return (0);
}
