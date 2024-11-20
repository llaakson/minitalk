/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:21:54 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/20 17:23:46 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "libft/libft.h"

int s_signal;
int spid;

int ft_get_bit(unsigned char *bit)
{
	int i;
	
	if (spid == 0)
		return (0);
	i = 8;
	while (i--)
	{
		if (s_signal == SIGUSR2)
		{
			*bit <<= 1;
			//write(1, "0",1);
		}
		else if (s_signal == SIGUSR1)
		{
			//*bit |= 1 << (7 - i);
			*bit = (*bit << 1) | 1;
			//write(1, "1",1);
		}
		//i++;
		kill(spid, SIGUSR2);
		usleep(10000);
	}
	//write(1,"\n",1);
	return (0);	
}

void *ft_message_length(void *str_size, int counter)
{
	int i;
	unsigned char	*temp;
	//ft_printf("counter %d\n", counter);	
	temp = (unsigned char *)str_size;
	i = 0;
	if (spid == 0)
		return (0);
	while (counter--)
	{
		ft_get_bit(&temp[counter]);
		i++;
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
	while (str_size)
	{
		ft_message_length(str+i,1);
		i++;
		str_size--;
	}
	ft_printf("%s\n", str);
	free (str);
	spid = 0;
}

void	ft_print_signal(int signum, siginfo_t *info, void* context)
{
	(void)context;
	spid = info->si_pid;
	s_signal = signum;
}

int	main(void)
{
	struct sigaction	siga;
	int str_size = 0;
	void	*str_size_ptr;

	siga.sa_sigaction = ft_print_signal;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL); // check these
	sigaction(SIGUSR2, &siga, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		//spid = 0;
		str_size = 0;
		str_size_ptr = ft_message_length(&str_size, sizeof(int));
		if (str_size_ptr && str_size > 0)
			ft_print_message(str_size);
	}
	return (0);
}

