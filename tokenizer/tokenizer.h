/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:47:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 15:51:28 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../minishell.h"

t_token	*tokenizer(char **splitcmd, t_mini *mini);
int		free_matrix(char **s);
void	scan_parenthesis(char **splitcmd, int *i, t_token **token_lst);
void	scan_redirections(char **splitcmd, int *i,
			t_token **token_lst);
void	scan_env_decl(char **splitcmd, int *i,
			t_token **token_lst, t_mini *mini);
int		scan_cmd(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_operator(char **splitcmd, int *i, t_token **token_lst);
int		verify_env_decl(char **splitcmd, int *i, t_mini *mini);
void	tok_add_back(t_token **lst, t_token *new);
char	*ft_strpbrk(char *str, char *set);
int		ft_isspace(char c);
int		ft_stralnum(char *str);
char	*ft_strbash_control(char *str);
void	initialize_previus(t_token *head);
void	*unlink_here_docs(t_list *here_docs_lst);
char	*here_doc_name(void);
char	*set_decl_name(char *word);
char	*set_decl_value(char *word);
int		set_decl_mode(char *word);

#endif
