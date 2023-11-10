/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_adding_only_for_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:44 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:34:46 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_good_for_env(t_declaration *node)
{
	char	*tmp;

	tmp = NULL;
	if (node->value != NULL && (ft_strchr(node->value, '\'')
			|| ft_strchr(node->value, '\"')))
	{
		tmp = ft_strndup(node->value, 1, ft_strlen(node->value) - 1);
		free(node->value);
		node->value = tmp;
		return (0);
	}
	return (1);
}

void	add_to_the_real_env(t_declaration *node, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
		i++;
	mini->env = ft_realloc(mini->env, sizeof(char *), i + 1, i + 2);
	mini->env[i] = ft_strdup(node->name);
	mini->env[i + 1] = 0;
	check_if_good_for_env(node);
	if (node->concatenation != 0)
		mini->env[i] = ft_strjoin_damn_you_leaks(mini->env[i], "=");
	if (node->value)
		mini->env[i] = ft_strjoin_damn_you_leaks(mini->env[i], node->value);
	g_last_exit_status_cmd = 0;
}
