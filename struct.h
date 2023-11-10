/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:41:13 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 16:22:19 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mini
{
	char	**env;
	char	**splitcmd;
}	t_mini;

typedef enum e_token_enum
{
	CMD_NAME,
	CMD_ARG,
	IN_FILE_TRUNC,
	HERE_DOC,
	OUT_FILE_TRUNC,
	OUT_FILE_APPEND,
	OPERATOR,
	ENV_VAR_DECL,
	ENV_VAR_UNSET,
	PARENTHESIS,
	NONE
}	t_token_enum;

typedef struct s_declaration
{
	int						concatenation;
	char					*name;
	char					*value;
	struct s_declaration	*next;
}	t_declaration;

typedef struct s_token
{
	t_token_enum	token;
	void			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum e_tree_enum
{
	SIMPLE_CMD,
	OP,
	PARENTHESI,
}	t_tree_enum;

typedef struct s_cmd
{
	t_token	*cmd_name;
	t_token	*cmd_arg;
}	t_cmd;

typedef struct s_simple_cmd
{
	t_token			*redir_list;
	struct s_cmd	*cmd;
	t_token			*env;
}	t_simple_cmd;

typedef struct s_tree
{
	t_tree_enum		type;
	void			*content;
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*prev;
	char			**env;
}	t_tree;

typedef struct s_parenthesis
{
	t_token	*redir_list;
	t_tree	*tree;
}	t_parenthesis;

#endif
