/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/15 16:03:01 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_char(int *str_size, char print_bit, int *bit_counter, int *int_count)
{	
	static char	*print_str;
	static int	check = 1;
	static int	i = 0;

	if (check == 1)
	{
		print_str = malloc(sizeof(char) * (*str_size + 1));
		check = 0;
	}
	print_str[i++] = print_bit;
	if (print_bit == '\0')
	{
		printf("%s\n", print_str);
		free(print_str);
		print_str = NULL;
		check = 1;
		i = 0;
		*str_size = 0;
		*bit_counter = 8;
		print_bit = '0';
		*int_count = 0;
		return ;
	}
	*bit_counter = 8;
}

void	ft_print_signal(int signum, siginfo_t *info, void *context)
{
	static int	str_size = 0;
	static int	bit_counter = 7;
	static char	print_bit = '0';
	static int	int_count = 0;

	(void)context;
	if (signum == SIGUSR2)
	{
		if (int_count++ < 32)
			str_size <<= 1;
		print_bit <<= 1;
	}
	else if (signum == SIGUSR1)
	{
		if (int_count++ < 32)
			str_size = (str_size << 1) | 1;
		print_bit = (print_bit << 1) | 1;
	}
	if (int_count > 32)
	{
		if (bit_counter == 0)
			print_char(&str_size, print_bit, &bit_counter, &int_count);
		bit_counter -= 1;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main_server(void)
{
	struct sigaction	siga;
	int					pid;

	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	pid = getpid();
	printf("%d\n", pid);
	while (1)
	{
		sleep (1);
	}
	return (0);
}
