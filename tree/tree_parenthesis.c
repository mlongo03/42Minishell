/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:23:37 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/10 16:44:55 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*copy_tok_parenthesis(t_token *to_copy)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->next = NULL;
	res->token = to_copy->token;
	res->value = to_copy->value;
	res->prev = NULL;
	return (res);
}

t_token	*skip_par_tokens(t_token *token_lst)
{
	t_token	*new_token_lst;
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	new_token_lst = NULL;
	token_lst = token_lst->next;
	while (token_lst && n_parenthesis)
	{
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, "(", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
		if (n_parenthesis)
		{
			tok_add_back(&new_token_lst, copy_tok_parenthesis(token_lst));
			token_lst = token_lst->next;
		}
	}
	return (new_token_lst);
}

t_token	*parenthesis_redirections(t_token *token_lst)
{
	t_token	*redir_lst;

	redir_lst = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			token_lst = skip_forward_parenthesis(token_lst);
		else if (token_lst->token == IN_FILE_TRUNC
			|| token_lst->token == OUT_FILE_TRUNC
			|| token_lst->token == HERE_DOC
			|| token_lst->token == OUT_FILE_APPEND)
			tok_add_back(&redir_lst, copy_tok(token_lst));
		token_lst = token_lst->next;
	}
	return (redir_lst);
}

void	free_tokens_parenthesis(t_token *token_lst)
{
	t_token			*tmp;

	while (token_lst)
	{
		tmp = token_lst;
		token_lst = token_lst->next;
		free(tmp);
	}
	free(token_lst);
}

t_parenthesis	*parenthesis_node(t_token *token_lst)
{
	t_parenthesis	*parenthesis_node;
	t_token			*new_token_lst;

	parenthesis_node = (t_parenthesis *)malloc(sizeof(t_parenthesis));
	parenthesis_node->redir_list = parenthesis_redirections(token_lst);
	new_token_lst = skip_par_tokens(token_lst);
	initialize_previus(new_token_lst);
	if (new_token_lst)
		while (new_token_lst->next)
			new_token_lst = new_token_lst->next;
	parenthesis_node->tree = tree_create(new_token_lst, OP);
	if (new_token_lst)
		while (new_token_lst->prev)
			new_token_lst = new_token_lst->prev;
	free_tokens_parenthesis(new_token_lst);
	return (parenthesis_node);
}
