/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:23:10 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/11 10:06:33 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_simple_cmd_args(char **args, t_mini *mini)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = expander(mini, args[i]);
		i++;
	}
}

void	free_exit(int exit_value)
{
	ft_free_all(var_container(NULL, NULL, NULL,
			GET_TOKENS), var_container(NULL,
			NULL, NULL, GET_TREE));
	free_matrix(((t_mini *)var_container(NULL,
				NULL, NULL, GET_MINI))->splitcmd);
	free_env(var_container(NULL, NULL, NULL, GET_MINI));
	exit(exit_value);
}

void	handle_redirections(t_token *redir_list, int in, int out, t_mini *mini)
{
	if (redir_list && have_inputs(redir_list))
	{
		if (execute_redirections_input(redir_list, in, mini))
			free_exit(1);
	}
	else
		dup_std_fd(in, STDIN_FILENO);
	if (redir_list && have_outputs(redir_list))
	{
		if (execute_redirections_output(redir_list, out, mini))
			free_exit(1);
	}
	else
		dup_std_fd(out, STDOUT_FILENO);
}

void	handle_redirections_builtin(t_token *redir_list, int in,
			int out, t_mini *mini)
{
	if (redir_list && have_inputs(redir_list))
	{
		if (execute_redirections_input(redir_list, in, mini))
		{
			g_last_exit_status_cmd = 1;
			return ;
		}
	}
	else
		dup_std_fd(in, STDIN_FILENO);
	if (redir_list && have_outputs(redir_list))
	{
		if (execute_redirections_output(redir_list, out, mini))
		{
			g_last_exit_status_cmd = 1;
			return ;
		}
	}
	else
		dup_std_fd(out, STDOUT_FILENO);
}

void	process_env(t_simple_cmd *simple_cmd, t_mini *mini)
{
	expander_env(simple_cmd->env->value, mini);
	execute_builtin_env(simple_cmd->env, mini);
}
