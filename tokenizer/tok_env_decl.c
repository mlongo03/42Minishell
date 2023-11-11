/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_decl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:43:54 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:50:33 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_declaration	*set_decl(char **splitcmd, int *i,
				t_token_enum token_enum)
{
	t_declaration	*res_decl;

	if (!splitcmd[*i] || ft_strbash_control(splitcmd[*i]))
		return (NULL);
	res_decl = (t_declaration *)malloc(sizeof(t_declaration));
	res_decl->next = NULL;
	res_decl->concatenation = 0;
	if (token_enum == ENV_VAR_DECL)
	{
		res_decl->concatenation = set_decl_mode(splitcmd[*i]);
		res_decl->name = set_decl_name(splitcmd[*i]);
		res_decl->value = set_decl_value(splitcmd[*i]);
	}
	else
	{
		res_decl->name = ft_strdup(splitcmd[*i]);
		res_decl->value = NULL;
	}
	*i += 1;
	return (res_decl);
}

void	add_decl_back(t_declaration **decl_lst, t_declaration *decl)
{
	static t_declaration	*tail = NULL;

	if (!(*decl_lst))
	{
		*decl_lst = decl;
		tail = *decl_lst;
	}
	else
	{
		tail->next = decl;
		tail = tail->next;
	}
	tail->next = NULL;
}

t_token	*set_token_env_id(char **splitcmd, int *i, t_mini *mini)
{
	t_token	*env_token;
	char	*expanded;
	char	*to_expand;

	to_expand = ft_strdup(splitcmd[*i]);
	expanded = expander(mini, to_expand);
	env_token = (t_token *)malloc(sizeof(t_token));
	env_token->next = NULL;
	if (ft_strlen(expanded) >= 5
		&& ft_strncmp(expanded, "unset", 5) == 0
		&& (ft_isspace(expanded[5]) || expanded[5] == 0))
		env_token->token = ENV_VAR_UNSET;
	else
		env_token->token = ENV_VAR_DECL;
	*i += 1;
	free(expanded);
	return (env_token);
}

int	verify_env_decl(char **splitcmd, int *i, t_mini *mini)
{
	char	*exp;
	char	*to_expand;

	if (!splitcmd[*i])
		return (1);
	to_expand = ft_strdup(splitcmd[*i]);
	exp = expander(mini, to_expand);
	if ((ft_strlen(exp) >= 6 && ft_strncmp(exp, "export", 6) == 0
			&& (ft_isspace(exp[6]) || exp[6] == 0)) || (ft_strlen(exp) >= 5
			&& ft_strncmp(exp, "unset", 5) == 0
			&& (ft_isspace(exp[5]) || exp[5] == 0))
		|| (ft_strlen(exp) >= 8 && ft_strncmp(exp + 1, "export", 6) == 0
			&& exp[0] == '"' && exp[7] == '"'
			&& (ft_isspace(exp[8]) || exp[8] == 0))
		|| (ft_strlen(exp) >= 7
			&& ft_strncmp(exp + 1, "unset", 5) == 0
			&& exp[0] == '"' && exp[6] == '"'
			&& (ft_isspace(exp[7]) || exp[7] == 0)))
	{
		free(exp);
		return (1);
	}
	free(exp);
	return (0);
}

void	scan_env_decl(char **splitcmd, int *i,
		t_token **token_lst, t_mini *mini)
{
	t_token			*token;
	t_declaration	*decl_lst;
	t_declaration	*tmpdecl;
	int				cursor;

	cursor = 0;
	decl_lst = NULL;
	if (!splitcmd[*i])
		return ;
	token = set_token_env_id(splitcmd, i, mini);
	while (splitcmd[*i])
	{
		scan_redirections(splitcmd, i, token_lst);
		cursor = *i;
		tmpdecl = set_decl(splitcmd, i, token->token);
		if (cursor == *i)
			break ;
		add_decl_back(&decl_lst, tmpdecl);
	}
	if (decl_lst != NULL)
		token->value = decl_lst;
	else
		token->value = NULL;
	token->next = NULL;
	tok_add_back(token_lst, token);
}
