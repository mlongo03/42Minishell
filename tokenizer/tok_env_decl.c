/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_decl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:43:54 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 16:37:51 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_decl_name(char *word)
{
	int		i;
	char	*err1;
	char	*err2;

	err1 = "=";
	err2 = "+=";
	i = 0;
	while (word[i] && word[i] != '=')
		i++;
	if (word[0] == '=')
		return (ft_substr(err1, 0, 1));
	else if (word[0] != '=' && word[i] == '=' && word[i - 1] == '+')
	{
		i--;
		if (word[0] == '+')
			return (ft_substr(err2, 0, 2));
	}
	else if (word[i] == 0)
		return (ft_substr(word, 0, ft_strlen(word)));
	return (ft_substr(word, 0, i));
}

char	*set_decl_value(char *word)
{
	int		start;
	int		end;
	char	*res;

	res = NULL;
	start = 0;
	end = 0;
	while (word[start] && word[start] != '=')
		start++;
	if (word[start] == 0)
		return (NULL);
	else if (word[start] == '=' && ft_isspace(word[start + 1]))
	{
		res = malloc(1);
		*res = 0;
		return (res);
	}
	start++;
	end = start;
	while (word[end])
		end++;
	return (ft_substr(word, start, end));
}

int	set_decl_mode(char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '=')
		i++;
	if (word[i] == '=' && word[i - 1] == '+')
		return (2);
	else if (word[i] == '=')
		return (1);
	else
		return (0);
}

t_declaration	*set_decl(char **splitcmd, int *i,
				t_token_enum token_enum, t_mini *mini)
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

t_token	*set_token_env_id(char **splitcmd, int *i)
{
	t_token	*env_token;

	env_token = (t_token *)malloc(sizeof(t_token));
	env_token->next = NULL;
	if (ft_strlen(splitcmd[*i]) >= 5
		&& ft_strncmp(splitcmd[*i], "unset", 5) == 0
		&& (ft_isspace(splitcmd[*i][5]) || splitcmd[*i][5] == 0))
		env_token->token = ENV_VAR_UNSET;
	else
		env_token->token = ENV_VAR_DECL;
	*i += 1;
	return (env_token);
}

int	verify_env_decl(char **splitcmd, int *i)
{
	if (!splitcmd[*i])
		return (0);
	else if ((ft_strlen(splitcmd[*i]) >= 6
			&& ft_strncmp(splitcmd[*i], "export", 6) == 0
			&& (ft_isspace(splitcmd[*i][6])
			|| splitcmd[*i][6] == 0))
			|| (ft_strlen(splitcmd[*i]) >= 5
			&& ft_strncmp(splitcmd[*i], "unset", 5) == 0
			&& (ft_isspace(splitcmd[*i][5])
			|| splitcmd[*i][5] == 0))
			|| (ft_strlen(splitcmd[*i]) >= 8
			&& ft_strncmp(splitcmd[*i] + 1, "export", 6) == 0
			&& splitcmd[*i][0] == '"'
			&& splitcmd[*i][7] == '"'
			&& (ft_isspace(splitcmd[*i][8])
			|| splitcmd[*i][8] == 0))
			|| (ft_strlen(splitcmd[*i]) >= 7
			&& ft_strncmp(splitcmd[*i] + 1, "unset", 5) == 0
			&& splitcmd[*i][0] == '"'
			&& splitcmd[*i][6] == '"'
			&& (ft_isspace(splitcmd[*i][7])
			|| splitcmd[*i][7] == 0)))
		return (1);
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
	token = set_token_env_id(splitcmd, i);
	while (splitcmd[*i])
	{
		scan_redirections(splitcmd, i, token_lst, mini);
		cursor = *i;
		tmpdecl = set_decl(splitcmd, i, token->token, mini);
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
