/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:43:45 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:51:53 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*scan_arg(char **splitcmd, int *i)
{
	char	*res;

	if (!splitcmd[*i] || ft_strbash_control(splitcmd[*i]))
		return (NULL);
	res = ft_substr(splitcmd[*i], 0, ft_strlen(splitcmd[*i]));
	*i += 1;
	return (res);
}

void	add_cmd_args(t_token *token_cmd_args, char *args, t_token **token_lst)
{
	token_cmd_args = (t_token *)malloc(sizeof(t_token));
	token_cmd_args->token = CMD_ARG;
	token_cmd_args->value = ft_split(args, ' ');
	free(args);
	token_cmd_args->next = NULL;
	tok_add_back(token_lst, token_cmd_args);
}

void	scan_args(char **splitcmd, int *i, t_token **token_lst)
{
	t_token	*token_cmd_args;
	char	*arg;
	char	*args;
	char	*tmp;

	arg = NULL;
	args = NULL;
	tmp = NULL;
	token_cmd_args = NULL;
	if (!splitcmd[*i])
		return ;
	while (splitcmd[*i])
	{
		scan_redirections(splitcmd, i, token_lst);
		arg = scan_arg(splitcmd, i);
		if (arg == NULL)
			break ;
		tmp = ft_strjoin(args, arg);
		free(args);
		free(arg);
		args = ft_strjoin(tmp, " ");
		free(tmp);
	}
	if (args != NULL)
		add_cmd_args(token_cmd_args, args, token_lst);
}

int	scan_cmd(char **splitcmd, int *i, t_token **token_lst, t_mini *mini)
{
	t_token	*token_cmd_name;
	char	*expanded;
	char	*to_expand;

	if (!splitcmd[*i] || ft_strbash_control(splitcmd[*i]))
		return (1);
	to_expand = ft_strdup(splitcmd[*i]);
	expanded = expander(mini, to_expand);
	if (!*expanded)
	{
		*i += 1;
		free(expanded);
		return (0);
	}
	free(expanded);
	token_cmd_name = (t_token *)malloc(sizeof(t_token));
	token_cmd_name->token = CMD_NAME;
	token_cmd_name->value = ft_substr(splitcmd[*i], 0, ft_strlen(splitcmd[*i]));
	token_cmd_name->next = NULL;
	*i += 1;
	scan_args(splitcmd, i, token_lst);
	tok_add_back(token_lst, token_cmd_name);
	return (1);
}
