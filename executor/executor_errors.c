/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:46:04 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 12:57:42 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_ambigous_redirection(void)
{
	ft_putstr_fd("minishell : ambigous redirection\n", 2);
	return (1);
}

void	error_is_a_directory(t_simple_cmd *simple_cmd, char **split_paths)
{
	p_error("minishell : ",
		simple_cmd->cmd->cmd_name->value, " is a directory\n");
	free_matrix(split_paths);
	free_exit(126);
}

void	error_command_not_found(t_simple_cmd *simple_cmd, char **split_paths)
{
	p_error("minishell : ",
		simple_cmd->cmd->cmd_name->value, " command not found\n");
	free_matrix(split_paths);
	free_exit(127);
}
