/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:37:57 by llaakson          #+#    #+#             */
/*   Updated: 2024/05/10 22:38:00 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*returnlist;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	returnlist = NULL;
	while (lst)
	{
		temp = f(lst->content);
		newlist = ft_lstnew(temp);
		if (!newlist)
		{
			del(temp);
			ft_lstclear(&returnlist, (*del));
			return (returnlist);
		}
		ft_lstadd_back(&returnlist, newlist);
		lst = lst->next;
	}
	return (returnlist);
}
