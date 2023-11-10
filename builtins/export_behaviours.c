/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:42:32 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	concatenation_export(t_declaration *node, int pos, t_mini *mini)
{
	char	*tmp_value;

	if (ft_strchr(mini->env[pos], '='))
		tmp_value = ft_strndup(mini->env[pos], 0, ft_strlen(mini->env[pos]));
	else
		tmp_value = ft_strdup(mini->env[pos]);
	free(mini->env[pos]);
	mini->env[pos] = tmp_value;
	if (!ft_strchr(mini->env[pos], '='))
		mini->env[pos] = ft_strjoin(node->name, "=");
	mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], node->value);
}

void	change_if_needed_env_ver(t_declaration *node, int pos, t_mini *mini)
{
	if (node->value != NULL)
	{
		free(mini->env[pos]);
		mini->env[pos] = ft_strdup(node->name);
		check_if_good_for_env(node);
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "=");
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], node->value);
	}
	else if (node->concatenation == 1)
	{
		free(mini->env[pos]);
		mini->env[pos] = ft_strdup(node->name);
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "=");
	}
}

int	check_doubles(t_declaration *node, t_mini *mini)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(node->name);
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], node->name, word_len) == 0
			&& (node->concatenation == 1 || node->concatenation == 0))
		{
			change_if_needed_env_ver(node, i, mini);
			return (1);
		}
		if (ft_strncmp(mini->env[i], node->name, word_len) == 0
			&& node->concatenation == 2)
		{
			concatenation_export(node, i, mini);
			return (1);
		}
		i++;
	}
	g_last_exit_status_cmd = 0;
	return (0);
}
