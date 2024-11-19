/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:11:55 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/19 00:07:12 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "libft/libft.h"

static int wait = 0; //make it global


int	print_char(int *str_size, char print_bit, int *bit_counter, int *int_count, int *current_pid)
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
		ft_printf("%s\n", print_str);
		free(print_str);
		print_str = NULL;
		check = 1;
		i = 0;
		*str_size = 0;
		*bit_counter = 8;
		print_bit = '0'; //reduntant ??
		*int_count = 0;
		*current_pid = 0;
		wait = 0;
		return (0);
	}
	*bit_counter = 8;
	return (1);
}

void ft_clean(int *str_size, char print_bit, int *bit_counter, int *int_count, int *current_pid)
{
		*str_size = 0;
		*bit_counter = 7;
		print_bit = '0'; //reduntant ??
		*int_count = 0;
		*current_pid = 0;
		wait = 0;
}
void	do_everything(int signum, int pid)
{
	static int	str_size = 0;
	static int	bit_counter = 7;
	static char	print_bit = '0';
	static int	int_count = 0;
	static int current_pid = 0;
	//int wait_counter = 0;

	if (getpid() == pid)
	{
		write(1, "clean\n",6);
		ft_clean(&str_size, print_bit, &bit_counter, &int_count, &current_pid);
		wait = 0;
		return ;
	}
	if (current_pid == 0)
		current_pid = pid;
	if (pid == current_pid)
	{
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
				if(!(print_char(&str_size, print_bit, &bit_counter, &int_count, &current_pid)))
				{
					bit_counter -= 1;
					kill(pid,SIGUSR2);
					return ;
				}
			bit_counter -= 1;
		}
		printf("%d\n",int_count);
		kill(pid, SIGUSR2);
		/*while (wait == 0)
		{
			//kill(pid, SIGUSR2);	
			usleep(100000);
			if (wait_counter == 50)
			{
				write (1, "fail\n", 5);
			}
			wait_counter++;
		}*/
		wait = 0;
	}
}

void	ft_print_signal(int signum, siginfo_t *info, void* context)
{
	(void)context;
	//write(1,"Handler\n", 8);
	do_everything(signum,info->si_pid);
}

int	main(void)
{
	struct sigaction	siga;
	int					pid;

	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1)
	{
		sleep (1);
		printf("wait %d\n",wait);
		if (wait == 1)
			kill(getpid(),SIGUSR2);
		wait = 1;
	}
	return (0);
}
