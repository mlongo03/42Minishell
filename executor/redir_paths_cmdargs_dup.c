/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_paths_cmdargs_dup.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:20:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/11 12:58:21 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_one_word(char	*input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			return (0);
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (input[i] && input[i] != quote)
				i++;
		}
		if (input[i])
			i++;
	}
	return (1);
}

int	execute_redirections_output(t_token *redir_list, int curr_out, t_mini *mini)
{
	char	*file_name;

	if (curr_out != STDOUT_FILENO)
		close(curr_out);
	while (redir_list)
	{
		file_name = (char *)redir_list->value;
		file_name = expander(mini, file_name);
		redir_list->value = file_name;
		if (!ft_is_one_word(file_name))
			return (error_ambigous_redirection());
		if (redir_list->token == OUT_FILE_TRUNC)
			curr_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else if (redir_list->token == OUT_FILE_APPEND)
			curr_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (curr_out == -1)
		{
			p_error("minishell : ", file_name, ": error creating file\n");
			return (1);
		}
		redir_list = redir_list->next;
	}
	dup_std_fd(curr_out, STDOUT_FILENO);
	return (0);
}

int	execute_redirections_input(t_token *redir_list, int curr_in, t_mini *mini)
{
	char	*file_name;

	if (curr_in != STDIN_FILENO)
		close(curr_in);
	while (redir_list)
	{
		file_name = (char *)redir_list->value;
		file_name = expander(mini, file_name);
		redir_list->value = file_name;
		if (!ft_is_one_word(file_name))
		{
			ft_putstr_fd("minishell : ambigous redirection\n", 2);
			return (1);
		}
		if (redir_list->token == IN_FILE_TRUNC || redir_list->token == HERE_DOC)
			curr_in = open(file_name, O_RDONLY);
		if (curr_in == -1)
		{
			p_error("minishell : ", file_name, "No such file or directory\n");
			return (1);
		}
		redir_list = redir_list->next;
	}
	dup_std_fd(curr_in, STDIN_FILENO);
	return (0);
}

char	**get_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	return (ft_split(env[i], ':'));
}

char	**get_cmd_args(t_simple_cmd *simple_cmd)
{
	char	**res;
	int		i;
	char	**args;

	i = 0;
	if (simple_cmd->cmd->cmd_arg != NULL)
	{
		args = (char **)simple_cmd->cmd->cmd_arg->value;
		while (args[i])
			i++;
	}
	res = (char **)malloc(sizeof(char *) * (i + 2));
	i = 1;
	res[0] = simple_cmd->cmd->cmd_name->value;
	if (simple_cmd->cmd->cmd_arg != NULL)
	{
		args = (char **)simple_cmd->cmd->cmd_arg->value;
		while (args[i - 1])
		{
			res[i] = args[i - 1];
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
