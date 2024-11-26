/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:58:19 by llaakson          #+#    #+#             */
/*   Updated: 2024/11/26 14:59:41 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"

int	set_pid(int spid)
{
	static int	static_pid = 0;

	if (spid == -1)
		return (static_pid);
	if (static_pid == 0 || spid == 0)
		static_pid = spid;
	if (static_pid == spid)
		return (0);
	if (static_pid != spid)
		return (-1);
	return (static_pid);
}
