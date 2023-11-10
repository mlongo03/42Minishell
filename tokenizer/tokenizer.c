/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:38 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 17:41:18 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_previus(t_token *head)
{
	t_token	*current;
	t_token	*prevnode;

	current = head;
	prevnode = NULL;
	while (current != NULL)
	{
		current->prev = prevnode;
		prevnode = current;
		current = current->next;
	}
}

void	debug_print_tokens(t_token *token_lst)
{
	t_declaration	*type_decl;
	char			*type_char;
	char			**args;
	int				i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->token == PARENTHESIS || token_lst->token == IN_FILE_TRUNC
			|| token_lst->token == HERE_DOC
			|| token_lst->token == OUT_FILE_APPEND
			|| token_lst->token == OUT_FILE_TRUNC
			|| token_lst->token == CMD_NAME
			|| token_lst->token == OPERATOR)
		{
			type_char = (char *)token_lst->value;
			printf("tipo : %d, contenuto : %s\n", token_lst->token, type_char);
		}
		else if (token_lst->token == ENV_VAR_DECL
			|| token_lst->token == ENV_VAR_UNSET)
		{
			type_decl = (t_declaration *)token_lst->value;
			printf("tipo : %d, contenuto : ", token_lst->token);
			while (type_decl)
			{
				printf("(var name : %s, var value : %s, conc mode : %d) ",
					type_decl->name, type_decl->value,
					type_decl->concatenation);
				type_decl = type_decl->next;
			}
			printf("\n");
		}
		else if (token_lst->token == CMD_ARG)
		{
			i = 0;
			args = (char **)token_lst->value;
			printf("tipo : %d, contenuto : (", token_lst->token);
			while (args[i])
			{
				printf(" %s", args[i]);
				i++;
			}
			printf(" )\n");
		}
		token_lst = token_lst->next;
	}
}

t_token	*tokenizer(char **splitcmd, t_mini *mini)
{
	t_token	*token_lst;
	int		i;
	int		cursor;

	i = 0;
	cursor = 0;
	token_lst = NULL;
	while (splitcmd[i])
	{
		cursor = i;
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst, mini);
		if (verify_env_decl(splitcmd, &i))
			scan_env_decl(splitcmd, &i, &token_lst, mini);
		else
		{
			if (!scan_cmd(splitcmd, &i, &token_lst, mini))
				continue ;
		}
		scan_redirections(splitcmd, &i, &token_lst, mini);
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst, mini);
		scan_operator(splitcmd, &i, &token_lst);
		if (cursor == i)
			break ;
	}
	initialize_previus(token_lst);
	return (token_lst);
}
