/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:43:58 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/31 11:06:11 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tok_add_back(t_token **lst, t_token *new)
{
	static t_token	*tail = NULL;

	if (!(*lst))
	{
		*lst = new;
		tail = *lst;
	}
	else
	{
		tail->next = new;
		tail = tail->next;
	}
	tail->next = NULL;
}
