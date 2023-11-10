/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:41:37 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 16:30:43 by mlongo           ###   ########.fr       */
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

void	execute_integrated(t_tree *tree, int curr_in,
		int curr_out, t_mini *mini)
{
	t_simple_cmd	*simple_cmd;
	t_token			*redir_list;

	if (!tree)
		return ;
	simple_cmd = (t_simple_cmd *)tree->content;
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_inputs(redir_list))
		{
			if (execute_redirections_input(redir_list, curr_in, mini))
			{
				free_matrix(((t_mini *)var_container(NULL, NULL, NULL, GET_MINI))->splitcmd);
				ft_free_all(var_container(NULL, NULL, NULL, GET_TOKENS),
					var_container(NULL, NULL, NULL, GET_TREE));
				exit(1);
			}
		}
	}
	else
		dup_std_fd(curr_in, STDIN_FILENO);
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_outputs(redir_list))
		{
			if (execute_redirections_output(redir_list, curr_out, mini))
			{
				free_matrix(((t_mini *)var_container(NULL, NULL, NULL, GET_MINI))->splitcmd);
				ft_free_all(var_container(NULL, NULL, NULL, GET_TOKENS),
					var_container(NULL, NULL, NULL, GET_TREE));
				exit(1);
			}
		}
	}
	else
		dup_std_fd(curr_out, STDOUT_FILENO);
	if (simple_cmd->cmd == NULL)
	{
		free_matrix(((t_mini *)var_container(NULL, NULL, NULL, GET_MINI))->splitcmd);
		ft_free_all(var_container(NULL, NULL, NULL, GET_TOKENS),
			var_container(NULL, NULL, NULL, GET_TREE));
		exit(1);
	}
	else
	{
		if (simple_cmd->cmd->cmd_arg)
			expander_simple_cmd_args(simple_cmd->cmd->cmd_arg->value, mini);
		execve_cmd(simple_cmd, mini);
	}
}

void	process_integrated(t_tree *tree, int curr_in,
		int curr_out, t_mini *mini)
{
	int	pid;
	int	exit_status;

	signal(SIGQUIT, ign);
	signal(SIGINT, ign);
	signal(SIGTERM, ign);
	pid = fork();
	if (pid == 0)
		execute_integrated(tree, curr_in, curr_out, mini);
	else
	{
		signal(SIGINT, signal_handler_execve);
		signal(SIGQUIT, signal_handler_execve);
		waitpid(pid, &exit_status, 0);
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		signal(SIGQUIT, ign);
		if (WIFEXITED(exit_status))
			g_last_exit_status_cmd = WEXITSTATUS(exit_status);
	}
}

int	is_builtin_command(t_tree *root, t_mini *mini)
{
	t_simple_cmd	*simple_cmd;
	char			*simple_name;

	simple_cmd = (t_simple_cmd *)root->content;
	if (simple_cmd->env)
		return (1);
	if (simple_cmd->cmd)
	{
		simple_name = (char *)simple_cmd->cmd->cmd_name->value;
		simple_name = expander(mini, simple_name);
		simple_cmd->cmd->cmd_name->value = simple_name;
		if (0 == ft_strcmp(simple_name, "cd")
			|| 0 == ft_strcmp(simple_name, "exit")
			|| 0 == ft_strcmp(simple_name, "echo")
			|| 0 == ft_strcmp(simple_name, "pwd")
			|| 0 == ft_strcmp(simple_name, "env")
		)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	execute_builtin_env(t_token *env, t_mini *mini)
{
	if (env->token == ENV_VAR_DECL)
		ft_export(env->value, mini);
	if (env->token == ENV_VAR_UNSET)
		g_last_exit_status_cmd = ft_unset(env->value, mini);
}

void	execute_builtin_cmd(t_cmd *cmd, t_mini *mini)
{
	char	**args;

	if (cmd->cmd_arg)
		args = cmd->cmd_arg->value;
	else
		args = NULL;
	if (ft_strcmp(cmd->cmd_name->value, "echo") == 0)
		g_last_exit_status_cmd = ft_echo(args);
	if (ft_strcmp(cmd->cmd_name->value, "cd") == 0)
		g_last_exit_status_cmd = ft_cd(args, mini);
	if (ft_strcmp(cmd->cmd_name->value, "pwd") == 0)
		g_last_exit_status_cmd = ft_pwd();
	if (ft_strcmp(cmd->cmd_name->value, "exit") == 0)
		ft_exit(args);
	if (ft_strcmp(cmd->cmd_name->value, "env") == 0)
		g_last_exit_status_cmd = ft_env(mini->env);
}
