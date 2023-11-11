/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:16:58 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:45:45 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree_parenthesis(t_parenthesis *par)
{
	free_tokens((t_token *)par->redir_list);
	free_tree((t_tree *)par->tree);
	free(par);
}

void	free_tree(t_tree *tree)
{
	t_simple_cmd	*simple_cmd;

	if (!tree)
		return ;
	if (tree->type == PARENTHESI)
		free_tree_parenthesis(tree->content);
	else if (tree->type == SIMPLE_CMD)
	{
		simple_cmd = (t_simple_cmd *)tree->content;
		free_tokens(simple_cmd->redir_list);
		free(simple_cmd->env);
		if (simple_cmd->cmd)
		{
			free(simple_cmd->cmd->cmd_arg);
			free_tokens(simple_cmd->cmd->cmd_name);
			free(simple_cmd->cmd);
		}
		free(simple_cmd);
	}
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

void	ft_free_all(t_token *token_lst, t_tree *tree)
{
	free_tokens(token_lst);
	free_tree(tree);
}
