/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:27:31 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:28:29 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_valid_wildcard(t_wild_split *wild, char **splitcmd, int i)
{
	free_matrix(wild->split_expanded);
	splitcmd[i] = wild->expanded;
}

void	valid_wildcard(t_wild_split *wild, char ***splitcmd, int i, int j)
{
	wild->end = env_rows(*splitcmd) - 1;
	*splitcmd = ft_realloc(*splitcmd, sizeof(char *),
			env_rows(*splitcmd),
			env_rows(*splitcmd) + env_rows(wild->split_expanded));
	wild->end_new = env_rows(*splitcmd)
		+ env_rows(wild->split_expanded) - 2;
	while (wild->end > i)
		(*splitcmd)[wild->end_new--] = (*splitcmd)[wild->end--];
	while (wild->split_expanded[j])
		(*splitcmd)[i++] = wild->split_expanded[j++];
	free(wild->expanded);
	free(wild->split_expanded);
}

char	**wildcard_split(char **splitcmd, t_mini *mini)
{
	int				i;
	int				j;
	t_wild_split	wild;

	i = 0;
	j = 0;
	while (splitcmd[i])
	{
		wild.expanded = ft_wildcard(splitcmd[i], mini);
		wild.split_expanded = ft_split(wild.expanded, ' ');
		if (wild.split_expanded[1])
		{
			if (i != 0 && ft_isredirection(splitcmd[i - 1]))
				not_valid_wildcard(&wild, splitcmd, i);
			else
				valid_wildcard(&wild, &splitcmd, i, j);
		}
		else
			not_valid_wildcard(&wild, splitcmd, i);
		if (splitcmd[i])
			i++;
	}
	return (splitcmd);
}
