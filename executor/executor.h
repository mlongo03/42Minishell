/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:37:51 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 10:06:16 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

void	execute(t_tree *tree, int curr_in, int curr_out, t_mini *mini);
void	redir_simple_command(t_token *r_list,
			t_simple_cmd *sim_cmd, int curr_out);
int		have_outputs(t_token *redir_list);
int		execute_redirections_output(t_token *redir_list,
			int curr_out, t_mini *mini);
void	dup_std_fd(int cur_in_out, int std_in_out);
int		execute_redirections_input(t_token *redir_list,
			int curr_in, t_mini *mini);
char	**get_paths(char **env);
char	**get_cmd_args(t_simple_cmd *simple_cmd);
char	*get_cmd_name_path(char *cmd_name, char **split_paths);
void	signal_handler_execve(int signum);
int		have_inputs(t_token *redir_list);
int		have_outputs(t_token *redir_list);
void	execve_cmd(t_simple_cmd *simple_cmd, t_mini *mini);
void	execute_integrated(t_tree *tree, int curr_in,
			int curr_out, t_mini *mini);
void	process_integrated(t_tree *tree, int curr_in,
			int curr_out, t_mini *mini);
int		is_builtin_command(t_tree *root, t_mini *mini);
void	execute_builtin_env(t_token *env, t_mini *mini);
void	execute_builtin_cmd(t_cmd *cmd, t_mini *mini);
void	expander_simple_cmd_args(char **args, t_mini *mini);
int		is_directory(const char *path);
void	dup_std_fd(int cur_in_out, int std_in_out);
void	expander_simple_cmd_args(char **args, t_mini *mini);
void	expander_env(t_declaration *env, t_mini *mini);
void	execute_builtin(t_tree *tree, int curr_in, int curr_out, t_mini *mini);
void	execute_and_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini);
void	execute_pipe_op(t_tree *root, int curr_in, int curr_out, t_mini *mini);
void	execute_simple_cmd(t_tree *tree, int curr_in,
			int curr_out, t_mini *mini);
void	free_exit(int exit_value);
void	handle_redirections(t_token *redir_list, int in, int out, t_mini *mini);
int		error_ambigous_redirection(void);
void	error_command_not_found(t_simple_cmd *simple_cmd, char **split_paths);
void	error_is_a_directory(t_simple_cmd *simple_cmd, char **split_paths);
void	handle_redirections_builtin(t_token *redir_list,
			int in, int out, t_mini *mini);
void	process_env(t_simple_cmd *simple_cmd, t_mini *mini);

#endif
