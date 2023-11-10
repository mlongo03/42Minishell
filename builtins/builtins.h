/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/09 15:41:37 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

int		ft_echo(char **command_line);
int		ft_cd(char **command_line, t_mini *mini);
int		ft_env(char **env);
int		copy_env(char **env, t_mini *all);
int		ft_pwd(void);
void	update_oldpwd(t_mini *mini);
void	update_pwd(t_mini *mini);
void	ft_export(t_declaration *node, t_mini *mini);
void	print_export(char **export_matrix);
void	sort_and_print_export(char **env);
char	**setting_the_matrix(char **env);
int		env_rows(char **env);
int		check_arguments_validation(char *command_line);
void	print_list(t_declaration *list);
void	add_export_env(char **env);
void	env_adding(char *final_string, char **env);
int		check_doubles(t_declaration *node, t_mini *mini);
char	*i_hate_this_strcpy_for_apix(char *dst, char *src);
char	*ft_strjoin_damn_you_leaks(char *s1, char *s2);
void	add_to_the_real_env(t_declaration *node, t_mini *mini);
int		check_if_good_for_env(t_declaration *node);
char	*ft_strndup(char *str, int start, int finish);
void	change_if_needed_env_ver(t_declaration *node, int pos, t_mini *mini);
void	concatenation_export(t_declaration *node, int pos, t_mini *mini);
char	**split_bt_nt_t_mc(char *str, char c);
int		ft_unset(t_declaration *node, t_mini *mini);
void	copy_check_unset(char *str, t_mini *mini);
void	swap_mat(char **str1, char **str2);
int		ft_exit(char **args);
#endif
