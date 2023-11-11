/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:48:20 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/11 16:04:49 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_equal(char *env)
{
	int	i;

	i = -1;
	while (env[++i] && env[i] != '=')
		;
	return (i);
}

void	print_export(char **export_matrix)
{
	int			i;
	size_t		j;
	size_t		len;

	i = -1;
	while (export_matrix[++i])
	{
		len = find_equal(export_matrix[i]);
		j = -1;
		printf("declare -x ");
		while (++j < len)
			printf("%c", export_matrix[i][j]);
		if (len < ft_strlen(export_matrix[i])
			&& ft_strchr(export_matrix[i], '='))
			printf("=\"%s\"", export_matrix[i] + len + 1);
		printf("\n");
	}
}

char	**setting_the_matrix(char **env)
{
	char	**the_export_copy;
	int		size;
	int		i;

	size = env_rows(env);
	the_export_copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!the_export_copy)
		printf("Errore nell'allocazione della memoria\n");
	i = -1;
	while (++i < size)
		the_export_copy[i] = ft_strdup(env[i]);
	the_export_copy[size] = NULL;
	return (the_export_copy);
}

void	sort_and_print_export(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**export_matrix;
	int		size;

	size = env_rows(env);
	export_matrix = setting_the_matrix(env);
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strcmp(export_matrix[j], export_matrix[j + 1]) > 0)
			{
				tmp = export_matrix[j];
				export_matrix[j] = export_matrix[j + 1];
				export_matrix[j + 1] = tmp;
			}
		}
	}
	print_export(export_matrix);
	free_matrix(export_matrix);
}

void	ft_export(t_declaration *node, t_mini *mini)
{
	if (!node)
		sort_and_print_export(mini->env);
	else
	{
		while (node)
		{
			if (!check_arguments_validation(node->name))
				g_last_exit_status_cmd = 1;
			else if (check_doubles(node, mini) == 0)
				add_to_the_real_env(node, mini);
			node = node->next;
		}
	}
}
