/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 17:41:25 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_enum	set_redir_type(char **splitcmd, int *i)
{
	t_token_enum	enum_tok;

	enum_tok = NONE;
	if (splitcmd[*i][0] == '>' && splitcmd[*i][1] == '>')
		enum_tok = OUT_FILE_APPEND;
	else if (splitcmd[*i][0] == '<' && splitcmd[*i][1] == '<')
		enum_tok = HERE_DOC;
	else if (splitcmd[*i][0] == '>')
		enum_tok = OUT_FILE_TRUNC;
	else if (splitcmd[*i][0] == '<')
		enum_tok = IN_FILE_TRUNC;
	*i += 1;
	return (enum_tok);
}

char	*set_redir_value(char **splitcmd, int *i)
{
	char	*res;

	res = ft_substr(splitcmd[*i], 0, ft_strlen(splitcmd[*i]));
	*i += 1;
	return (res);
}

char	*here_doc_name(void)
{
	int				here_docs;
	char			*prefix;
	char			*res;
	char			*suffix;

	here_docs = 0;
	prefix = ".here_docs-";
	while (1)
	{
		suffix = ft_itoa(here_docs);
		res = ft_strjoin(prefix, suffix);
		if (access(res, R_OK | W_OK) != 0)
		{
			free(suffix);
			break ;
		}
		free(suffix);
		free(res);
		here_docs++;
	}
	return (res);
}

void	*unlink_here_docs(t_list *here_docs_lst)
{
	while (here_docs_lst)
	{
		unlink((char *)here_docs_lst->content);
		here_docs_lst = here_docs_lst->next;
	}
	return (NULL);
}

void	scan_redirections(char **splitcmd, int *i,
	t_token **token_lst)
{
	t_token	*token;

	if (!splitcmd[*i])
		return ;
	while (splitcmd[*i] && ((splitcmd[*i][0] == '>' && splitcmd[*i][1] == '>')
			|| (splitcmd[*i][0] == '<' && splitcmd[*i][1] == '<')
			|| splitcmd[*i][0] == '>' || splitcmd[*i][0] == '<'))
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->token = set_redir_type(splitcmd, i);
		if (token->token == NONE)
			return ;
		if (token->token == HERE_DOC)
		{
			token->value = handle_list_heredocs(GET);
			(*i)++;
		}
		else
			token->value = set_redir_value(splitcmd, i);
		token->next = NULL;
		tok_add_back(token_lst, token);
	}
}
