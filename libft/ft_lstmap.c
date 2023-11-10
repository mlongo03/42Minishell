/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:51:07 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/05 17:20:57 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (list);
}
