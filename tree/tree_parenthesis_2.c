/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parenthesis_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:44:44 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 16:44:57 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_parenthesis(t_token *token_lst)
{
	while (token_lst->next && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
}
