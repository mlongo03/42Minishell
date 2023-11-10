/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_more_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:40:20 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arguments_validation(char *identity_name_only)
{
	int	i;

	i = 0;
	if (!ft_isalpha(identity_name_only[0]))
	{
		printf("\033[1;31mbash: export: `%s':not a valid identifier\n\033\e[0m",
			identity_name_only);
		g_last_exit_status_cmd = 1;
		return (0);
	}
	while (identity_name_only[i])
	{
		if (!ft_isalnum(identity_name_only[i]) && identity_name_only[i] != '='
			&& identity_name_only[i] != '+')
		{
			printf("\033[31mbash: export: `%s': not a valid identifier\n\e[0m",
				identity_name_only);
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
