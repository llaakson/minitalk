/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:52 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/04 20:52:17 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int convert_binary(char *argv, int id)
{
	int i;
	int bit;
	int c;

	c = 0; 
	i = 8 * strlen(argv);
	while (i--)
	{
		bit = argv[c] >> i & 1;
		if (bit == 0)
			kill(id,30);
		if (bit == 1)
			kill(id,17);
		printf("%d\n", bit);
		c++;
	}
	return(0);
}

int	main(int argc, char **argv)
{
	argc += 1;
	int id = atoi(argv[1]);
	convert_binary(argv[2], id);
	
	return (0);
}
