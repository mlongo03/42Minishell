/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:28:00 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 11:37:16 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*copy_tok(t_token *to_copy)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->next = NULL;
	res->token = to_copy->token;
	if (to_copy->token == OPERATOR || to_copy->token == OUT_FILE_APPEND
		|| to_copy->token == OUT_FILE_TRUNC
		|| to_copy->token == IN_FILE_TRUNC || to_copy->token == CMD_NAME)
		res->value = ft_strdup((char *)to_copy->value);
	else
		res->value = to_copy->value;
	res->prev = NULL;
	return (res);
}

t_token	*skip_forward_parenthesis(t_token *token_lst)
{
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	while (token_lst->next && n_parenthesis)
	{
		token_lst = token_lst->next;
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, "(", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
	}
	return (token_lst);
}

t_token	*skip_back_parenthesis(t_token *token_lst)
{
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	while (token_lst->prev && n_parenthesis)
	{
		token_lst = token_lst->prev;
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, ")", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
	}
	if (token_lst->prev != NULL)
		return (token_lst->prev);
	else
		return (token_lst);
}
