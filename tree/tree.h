/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:19:48 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 12:36:22 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../minishell.h"

t_tree			*tree_create(t_token *token_lst, t_tree_enum calling);
t_parenthesis	*parenthesis_node(t_token *token_lst);
t_token			*parenthesis_redirections(t_token *token_lst);
t_token			*skip_par_tokens(t_token *token_lst);
int				verify_parenthesis(t_token *token_lst);
t_token			*skip_back_parenthesis(t_token *token_lst);
t_token			*skip_forward_parenthesis(t_token *token_lst);
t_token			*copy_tok(t_token *to_copy);
t_simple_cmd	*simple_cmd_redirections(t_token *token_lst);
void			simple_cmd(t_token *token_lst, t_simple_cmd *simple_cmd);
void			free_tokens(t_token *token_lst);

#endif
