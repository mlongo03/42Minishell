/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_more_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/11 12:57:42 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_error(char *first, char *var, char *second)
{
	ft_putstr_fd(first, 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(second, 2);
}

int	check_arguments_validation(char *identity_name_only)
{
	int	i;

	i = 0;
	if (!ft_isalpha(identity_name_only[0]))
	{
		p_error("minishell: export: '",
			identity_name_only, "': not a valid identifier\n");
		g_last_exit_status_cmd = 1;
		return (0);
	}
	while (identity_name_only[i])
	{
		if (!ft_isalnum(identity_name_only[i]) && identity_name_only[i] != '='
			&& identity_name_only[i] != '+')
		{
			p_error("minishell: export: '",
				identity_name_only, "': not a valid identifier");
			g_last_exit_status_cmd = 1;
			return (0);
		}
		else if (identity_name_only[i] == '=')
			return (1);
		i++;
	}
	return (1);
}

void	print_list(t_declaration *list)
{
	while (list != NULL)
	{
		printf("name %s, conc %d, value %s\n", list->name,
			list->concatenation, list->value);
		list = list->next;
	}
}
