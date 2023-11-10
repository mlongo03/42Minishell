/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_env_add.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:38:43 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:40:57 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_adding(char *final_string, char **env)
{
	size_t	new_size;

	new_size = env_rows(env) + 1;
	env = ft_realloc(env, sizeof(char *), new_size, new_size + 1);
	env[new_size - 1] = ft_strdup(final_string);
	env[new_size] = 0;
}

void	add_export_env(char **env)
{
	char	*final_string;

	env_adding(final_string, env);
	free(final_string);
}
