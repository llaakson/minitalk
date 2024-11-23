/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:21:54 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/21 23:25:22 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "libft/libft.h"

static int s_signal;
static int spid;

int ft_get_bit(unsigned char *bit, int static_pid)
{
	int i;
	
	i = 0;
	static_pid = 0;
	//printf("static pid %d spid %d \n", static_pid, spid);
	while (8 > i)
	{
		while (!s_signal)
		{
			usleep(100000);
			if (!s_signal)
				return (0);
		}
		if (s_signal == SIGUSR1)
			*bit |= 1 << (7 - i);
		i++;
		s_signal = 0;
		if (kill(spid, SIGUSR2) == -1)
			write(2, "Error sending signal\n", 21);
	}
	//write(1,"\n",1);
	return (1);	
}

void *ft_message_length(void *str_size, int counter, int static_pid)
{
	unsigned char	*temp;
	int i;
	
	ft_bzero(str_size,counter);
	temp = (unsigned char *)str_size;
	i = 0;
	while (i < counter)
	{
		if (!(ft_get_bit(&temp[i],static_pid)))
			return (NULL);
		i++;
	}
	return (str_size);	
}

void	ft_print_message(int str_size,int static_pid)
{
	char *str;
	
	//ft_printf("\nMessage size is %d   \n", str_size);
	str = malloc(str_size + 1);
	if (!str)
	{
		write(2, "Failed to allocate memory\n", 26);
		return ;
	}
	if(!(ft_message_length(str, str_size, static_pid)));
	{
		free(str);
		write(2, "Signal lost\n", 12);
		return ;
	}
	str[str_size] = '\0';
	ft_printf("%s\n", str);
	free (str);
}

void	ft_print_signal(int signum, siginfo_t *info, void* context)
{
	(void)context;

	if (spid == 0)
		spid = info->si_pid;
	if (spid == info->si_pid)
		s_signal = signum;
	//if (signum == SIGUSR2)
	//	s_signal *= -1;
	//if (signum == SIGUSR1)
	//	spid = info->si_pid;
}

int	main(void)
{
	struct sigaction	siga;
	int str_size = 0;
	void	*str_size_ptr;
	static int static_pid;

	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		static_pid = 0;
		spid = 0;
		str_size = 0;
		str_size_ptr = ft_message_length(&str_size, sizeof(int),static_pid);
		if (str_size_ptr && str_size > 0)
			ft_print_message(str_size, static_pid);
	}
	return (0);
}

