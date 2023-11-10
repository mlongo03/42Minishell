/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_signal_have_cmdpath.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:27:59 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 19:10:11 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_directory(const char *path)
{
	DIR *dir = opendir(path);

	if (dir != NULL)
	{
		closedir(dir);
		return 1;
	}
	else
		return 0;
}

char	*get_cmd_name_path(char *cmd_name, char **split_paths)
{
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	if (!split_paths)
		return (NULL);
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	while (split_paths[i])
	{
		path = ft_strjoin(split_paths[i], "/");
		tmp = path;
		path = ft_strjoin(path, cmd_name);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	signal_handler_execve(int signum)
{
	if (signum == SIGINT)
		g_last_exit_status_cmd = 130;
	if (signum == SIGQUIT)
		g_last_exit_status_cmd = 131;
}

int	have_inputs(t_token *redir_list)
{
	while (redir_list)
	{
		if (redir_list->token == HERE_DOC || redir_list->token == IN_FILE_TRUNC)
			return (1);
		redir_list = redir_list->next;
	}
	return (0);
}

int	have_outputs(t_token *redir_list)
{
	while (redir_list)
	{
		if (redir_list->token == OUT_FILE_TRUNC || redir_list->token == OUT_FILE_APPEND)
			return (1);
		redir_list = redir_list->next;
	}
	return (0);
}

void	execve_cmd(t_simple_cmd *simple_cmd, t_mini *mini)
{
	char	**split_paths;
	char	*cmd_name;
	char	**cmd_args;

	cmd_name = NULL;
	split_paths = get_paths(mini->env);
	if (is_directory(simple_cmd->cmd->cmd_name->value))
	{
		printf("minishell : %s is a directory\n", (char *)simple_cmd->cmd->cmd_name->value);
		free_matrix(split_paths);
		ft_free_all(var_container(NULL, NULL, NULL, GET_TOKENS), var_container(NULL, NULL, NULL, GET_TREE));
		free_matrix(((t_mini *)var_container(NULL, NULL, NULL, GET_MINI))->splitcmd);
		free_env(var_container(NULL, NULL, NULL, GET_MINI));
		exit(126);
	}
	if (split_paths != NULL)
	{
		split_paths[0] = ft_strtrim(split_paths[0], "PATH=");
		cmd_name = get_cmd_name_path((char *)simple_cmd->cmd->cmd_name->value, split_paths);
	}
	if (split_paths == NULL || cmd_name == NULL)
	{
		printf("minishell : %s command not found\n", (char *)simple_cmd->cmd->cmd_name->value);
		free_matrix(split_paths);
		ft_free_all(var_container(NULL, NULL, NULL, GET_TOKENS), var_container(NULL, NULL, NULL, GET_TREE));
		free_matrix(((t_mini *)var_container(NULL, NULL, NULL, GET_MINI))->splitcmd);
		free_env(var_container(NULL, NULL, NULL, GET_MINI));
		exit(127);
	}
	cmd_args = get_cmd_args(simple_cmd);
	free_matrix(split_paths);
	execve(cmd_name, cmd_args, mini->env);
}
