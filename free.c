/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:42:55 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 17:44:52 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
		free(mini->env[i++]);
	free(mini->env);
	free(mini);
}

void	free_declarations(t_declaration *type_decl)
{
	t_declaration	*tmpdecl;

	while (type_decl)
	{
		tmpdecl = type_decl;
		if (tmpdecl->name)
			free(tmpdecl->name);
		if (tmpdecl->value)
			free(tmpdecl->value);
		type_decl = type_decl->next;
		free(tmpdecl);
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_tokens(t_token *token_lst)
{
	t_token			*tmp;

	while (token_lst)
	{
		if (token_lst->token == OPERATOR || token_lst->token == OUT_FILE_APPEND
			|| token_lst->token == OUT_FILE_TRUNC
			|| token_lst->token == IN_FILE_TRUNC
			|| token_lst->token == OPERATOR || token_lst->token == CMD_NAME)
			free(token_lst->value);
		else if (token_lst->token == ENV_VAR_DECL
			|| token_lst->token == ENV_VAR_UNSET)
			free_declarations(token_lst->value);
		else if (token_lst->token == CMD_ARG)
			free_args(token_lst->value);
		tmp = token_lst;
		token_lst = token_lst->next;
		free(tmp);
	}
	free(token_lst);
}
