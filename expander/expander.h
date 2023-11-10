/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/09 15:31:41 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

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

int				env_rows2(t_mini *shell_data);
int				put_arguments_in_list(t_declaration *identity,
					char *command_line);
void			insert_declaration(t_declaration **list, int concatenation,
					const char *name, const char *value);
void			print_list(t_declaration *list);
void			arguments_separation(char **command_line, int conc,
					t_declaration **identity);
void			add_env(t_mini *shell_data, t_declaration **values);
void			super_strjoin(t_mini *shell_data, t_declaration *values);
char			*expander(t_mini *shell_data, char *input);
char			*handle_apix_case(char *ret);
char			**matrix_directory(t_mini *shell_data);
int				ft_strcmp_env(const char *input, const char *env);
void			stampaMatriceChar(char **matrice);
void			ft_strncat(char **dest, char c, int nb);
char			*ft_strcat(char *dest, char *src);
int				jump_to_next(char *str);
char			*expand_env_variable(t_mini *shell_data, const char *var_name);
char			*expand_variable(t_mini *shell_data, char *input, int *i);
char			*realloc_concat_free_norm(char *ret, char *v);
char			*manage_dollar_norm(char *input, int *i,
					char *ret, t_mini *shell_data);
int				quote_logic_norm(char *input, char **ret,
					char quote, t_mini *shell_data);
char			*order_result(char *result);
void			selection_sort(char **array);
void			swapstrings(char **a, char **b);
char			*ft_wildcard(char *input, t_mini *mini);
int				filter_word(char *input, char *filename, t_mini *mini);
int				word_middle_filter(char *filter, char *filename, int *i);
int				word_start_filter(char *filter, char *filename, int *i);
int				word_end_filter(char *filter, char *filename, int *i);
char			*expand_strbefore(char *input, int i, t_mini *mini);
int				move_to_wildcard(char *input);
int				is_wildcard_present(char *input);
int				check_wildcard_before(char *input, int i);
void			close_free_dir(struct dirent *entry, char *dirname, DIR *dir);
void			open_read_getcwd(char **dirname, DIR **dir,
					struct dirent **entry);
#endif
