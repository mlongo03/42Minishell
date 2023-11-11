/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:30:58 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/11 10:03:00 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_env(t_declaration *env, t_mini *mini)
{
	while (env)
	{
		env->name = expander(mini, env->name);
		if (env->value)
			env->value = expander(mini, env->value);
		env = env->next;
	}
}

void	execute_builtin(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	t_simple_cmd	*simple_cmd;
	t_token			*redir_list;
	int				starting_in;
	int				starting_out;

	if (!tree)
		return ;
	starting_in = dup(fileno(stdin));
	starting_out = dup(fileno(stdout));
	simple_cmd = (t_simple_cmd *)tree->content;
	redir_list = (t_token *)simple_cmd->redir_list;
	handle_redirections_builtin(redir_list, curr_in, curr_out, mini);
	if (simple_cmd->cmd == NULL)
	{
		if (simple_cmd->env != NULL)
			process_env(simple_cmd, mini);
	}
	else
	{
		if (simple_cmd->cmd->cmd_arg)
			expander_simple_cmd_args(simple_cmd->cmd->cmd_arg->value, mini);
		execute_builtin_cmd(simple_cmd->cmd, mini);
	}
	dup_std_fd(starting_in, STDIN_FILENO);
	dup_std_fd(starting_out, STDOUT_FILENO);
}

void	execute_simple_cmd(t_tree *tree, int curr_in,
			int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	if (is_builtin_command(tree, mini))
		execute_builtin(tree, curr_in, curr_out, mini);
	else
		process_integrated(tree, curr_in, curr_out, mini);
}

void	execute_pipe_op(t_tree *root, int curr_in, int curr_out, t_mini *mini)
{
	int	piping[2];
	int	pid_left;
	int	pid_right;
	int	exit_status;

	pipe(piping);
	pid_left = fork();
	if (!pid_left)
	{
		close(piping[0]);
		execute(root->left, curr_in, piping[1], mini);
		free_exit(g_last_exit_status_cmd);
	}
	pid_right = fork();
	if (!pid_right)
	{
		close(piping[1]);
		execute(root->right, piping[0], curr_out, mini);
		free_exit(g_last_exit_status_cmd);
	}
	close(piping[0]);
	close(piping[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	g_last_exit_status_cmd = WEXITSTATUS(exit_status);
}

void	execute_and_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out, mini);
	if (g_last_exit_status_cmd == 0)
		execute(tree->right, curr_in, curr_out, mini);
}
