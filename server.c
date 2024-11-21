/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:21:54 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/20 23:14:29 by llaakson         ###   ########.fr       */
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

int ft_get_bit(unsigned char *bit)
{
	int i;
	
	i = 8;
	while (i--)
	{
		while (!s_signal)
		{
			usleep(1000000);
			if (!s_signal)
				return(0);
		}
		if (s_signal == SIGUSR2)
		{
			*bit <<= 1;
			//write(1, "0",1);
		}
		if (s_signal == SIGUSR1) //pid > 0)
		{
			*bit = (*bit << 1) | 1;
			//write(1, "1",1);
		}
		s_signal = 0;
		kill(spid, SIGUSR2);
	}
	//write(1,"\n",1);
	return (1);	
}

void *ft_message_length(void *str_size, int counter)
{
	unsigned char	*temp;
	int i;
	
	ft_bzero(str_size,counter);
	temp = (unsigned char *)str_size;
	i = 0;
	while (counter--)
	{
		if (!(ft_get_bit(&temp[counter])))
			return (NULL);
	}
	return (str_size);	
}

void	ft_print_message(int str_size)
{
	char *str;
	
	ft_printf("\nMessage size is %d   \n", str_size);
	//write(1,"malloc\n",7);
	str = malloc(str_size + 1);
	int i = 0;
	while (str_size--)
	{
		if(!(ft_message_length(str+i,1)))
		{
			free (str);
			return ;
		}
		i++;
	}
	str[i] = '\0';
	ft_printf("%s\n", str);
	free (str);
}

void	ft_print_signal(int signum, siginfo_t *info, void* context)
{
	(void)context;
	//if (spid < 0)
	//	spid *= -1;
	if (spid == 0)
		spid = info->si_pid;
	if (spid == info->si_pid)
		s_signal = signum;
		
	//s_signal = signum;
	//if (signum == SIGUSR2)
	//	spid *= -1;
}

int	main(void)
{
	struct sigaction	siga;
	int str_size = 0;
	void	*str_size_ptr;

	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		spid = 0;
		str_size = 0;
		str_size_ptr = ft_message_length(&str_size, sizeof(int));
		if (str_size_ptr && str_size > 0)
			ft_print_message(str_size);
	}
	return (0);
}

