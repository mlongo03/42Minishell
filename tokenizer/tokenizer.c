/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:38 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:50:47 by mlongo           ###   ########.fr       */
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

t_token	*tokenizer(char **splitcmd, t_mini *mini)
{
	t_token	*token_lst;
	int		i;
	int		cursor;

	i = 0;
	cursor = 1;
	token_lst = NULL;
	while (splitcmd[i] && cursor != i)
	{
		cursor = i;
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		if (verify_env_decl(splitcmd, &i, mini))
			scan_env_decl(splitcmd, &i, &token_lst, mini);
		else
			if (!scan_cmd(splitcmd, &i, &token_lst, mini))
				continue ;
		scan_redirections(splitcmd, &i, &token_lst);
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		scan_operator(splitcmd, &i, &token_lst);
	}
	initialize_previus(token_lst);
	return (token_lst);
}
