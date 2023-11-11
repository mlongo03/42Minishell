/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:35:53 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 11:47:49 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include <time.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>
# include "global.h"
# include "./lexer/lexer.h"
# include "./libft/libft.h"
# include "./tokenizer/tokenizer.h"
# include "./tree/tree.h"
# include "./executor/executor.h"
# include "./builtins/builtins.h"
# include "./gnl/get_next_line_bonus.h"
# include "./expander/expander.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# define SET 10
# define GET_TREE 11
# define GET_TOKENS 12
# define GET_MINI 13

void	signal_handler(int signum);
void	ign(int signum);
void	*var_container(t_token *token_lst, t_tree *tree, t_mini *mini, int op);
void	ft_free_all(t_token *token_lst, t_tree *tree);
void	free_tree(t_tree *tree);
void	free_tokens(t_token *token_lst);
void	printTree(t_tree *node, int level, char *message);
void	free_env(t_mini *mini);
int		ft_isredirection(char *str);
void	increment_shlvl(t_mini *mini);

#endif
