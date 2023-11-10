/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:48:37 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 15:49:22 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define START 0
# define ADD 1
# define LIST 2
# define GET 3

# include "../minishell.h"

char	*handle_quotes(char *str, char *res, int *i, int *j);
char	*handle_two(char *str, char *res, int *i, int *j);
char	*handle_one(char *str, char *res, int *i, int *j);
int		count_syntax(char *str);
char	*fix_white_spaces(char *str);
char	*fix_syntax(char *str);
void	*handle_list_heredocs(int op);
void	handle_here_doc(char *del, t_mini *mini);
void	del(void *str);
char	*create_del(char *s);
int		check(char *s, t_mini *mini);
int		check_parentheses(char *s, int *i);
int		check_number(char *s);
int		check_quote(char *s);
int		check_operator(char *s, int *i);
int		counter(int count);
int		is_op(char *c);
int		is_red(char *c);
int		is_op_or_red(char *s, int *i);
int		is_one_char(char *c);
int		is_two_char(char *c);
int		is_double(char *s, int *i);
#endif
