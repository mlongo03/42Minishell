/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:16:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:37:06 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fix_mat(t_mini *mini, int i)
{
	while (mini->env[i + 1])
	{
		swap_mat(&mini->env[i], &mini->env[i + 1]);
		i++;
	}
	mini->env[i] = 0;
}

void	copy_check_unset(char *str, t_mini *mini)
{
	int		i;
	int		j;

	i = -1;
	while (mini->env[++i])
	{
		j = -1;
		while (mini->env[i][++j] == '=' && mini->env[i][j])
			;
		if (ft_strncmp(mini->env[i], str, j) == 0)
		{
			if (ft_strncmp(mini->env[i], str,
					ft_strlen(str)) == 0)
			{
				free(mini->env[i]);
				fix_mat(mini, i);
				break ;
			}
		}
	}
}

int	ft_unset(t_declaration *node, t_mini *mini)
{
	int				i;

	i = 0;
	if (!node)
		return (0);
	while (node)
	{
		copy_check_unset(node->name, mini);
		node = node->next;
	}
	return (0);
}
