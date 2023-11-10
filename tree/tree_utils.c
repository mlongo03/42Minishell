/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:28:00 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 14:48:01 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	simple_cmd(t_token *token_lst, t_simple_cmd *simple_cmd)
{
	simple_cmd->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	simple_cmd->cmd->cmd_arg = NULL;
	simple_cmd->cmd->cmd_name = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == CMD_ARG)
		{
			tok_add_back(&simple_cmd->cmd->cmd_arg, copy_tok(token_lst));
			tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst->next));
			return ;
		}
		else if (token_lst->token == CMD_NAME)
		{
			tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst));
			return ;
		}
		else if (token_lst->token == ENV_VAR_DECL
			|| token_lst->token == ENV_VAR_UNSET)
		{
			tok_add_back(&simple_cmd->env, copy_tok(token_lst));
			free(simple_cmd->cmd);
			simple_cmd->cmd = NULL;
			return ;
		}
		else
			token_lst = token_lst->next;
	}
	if (simple_cmd->cmd->cmd_arg == NULL && simple_cmd->cmd->cmd_name == NULL)
	{
		free(simple_cmd->cmd);
		simple_cmd->cmd = NULL;
	}
}

t_simple_cmd	*simple_cmd_redirections(t_token *token_lst)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	simple_cmd->redir_list = NULL;
	simple_cmd->cmd = NULL;
	simple_cmd->env = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			token_lst = skip_forward_parenthesis(token_lst);
		else if (token_lst->token == IN_FILE_TRUNC
			|| token_lst->token == OUT_FILE_TRUNC
			|| token_lst->token == HERE_DOC
			|| token_lst->token == OUT_FILE_APPEND)
			tok_add_back(&simple_cmd->redir_list, copy_tok(token_lst));
		token_lst = token_lst->next;
	}
	return (simple_cmd);
}

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
