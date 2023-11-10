/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:48:48 by mlongo            #+#    #+#             */
/*   Updated: 2023/09/02 16:18:57 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->prev = ft_lstlast(*lst);
	ft_lstlast(*lst)->next = new;
}
