/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:36:35 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 11:37:46 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tok_cmd_add(t_simple_cmd *simple_cmd, t_token *token_lst)
{
	if (token_lst->token == CMD_ARG)
	{
		tok_add_back(&simple_cmd->cmd->cmd_arg, copy_tok(token_lst));
		tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst->next));
		return (0);
	}
	else if (token_lst->token == CMD_NAME)
	{
		tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst));
		return (0);
	}
	else if (token_lst->token == ENV_VAR_DECL
		|| token_lst->token == ENV_VAR_UNSET)
	{
		tok_add_back(&simple_cmd->env, copy_tok(token_lst));
		free(simple_cmd->cmd);
		simple_cmd->cmd = NULL;
		return (0);
	}
	return (1);
}

void	simple_cmd(t_token *token_lst, t_simple_cmd *simple_cmd)
{
	simple_cmd->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	simple_cmd->cmd->cmd_arg = NULL;
	simple_cmd->cmd->cmd_name = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (!tok_cmd_add(simple_cmd, token_lst))
			return ;
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
