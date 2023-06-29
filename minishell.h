/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:36 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/29 17:12:01 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6

typedef struct s_content
{
	char	**cmd;
	int		op;
}	t_content;

typedef struct s_tree
{
	struct s_content	*content;
	struct s_tree		*before;
	struct s_tree		*right;
	struct s_tree		*left;
}	t_tree;

typedef struct s_data
{
	int		temp_input;
	int		temp_output;
	int		temp_error;
	t_tree	*tree;
}	t_data;

#endif
