/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:20:54 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 15:01:46 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	printTree(t_tree *node, int level, char *message)
// {
// 	if (node == NULL) {
// 		return;
// 	}
// 	for (int i = 0; i < level; i++) {
// 		printf("  ");
// 	}
// 	printf("%s\n", message);
// 	for (int i = 0; i < level; i++) {
// 		printf("  ");
// 	}

// 	if (node->type == SIMPLE_CMD) {
// 		t_simple_cmd *cmd = (t_simple_cmd *)node->content;
// 		printf("SIMPLE_CMD\n");
// 		debug_print_tokens(cmd->redir_list);
// 		for (int i = 0; i < level; i++) {
// 			printf("  ");
// 		}
// 		debug_print_tokens(cmd->cmd->cmd_arg);
// 		for (int i = 0; i < level; i++) {
// 			printf("  ");
// 		}
// 		debug_print_tokens(cmd->cmd->cmd_name);
// 		debug_print_tokens(cmd->env);
// 	} else if (node->type == OP) {
// 		printf("OP\n");
// 		char *cmd = (char *)node->content;
// 		printf("content : %s\n", cmd);
// 	} else if (node->type == PARENTHESI) {
// 		printf("PARENTHESIS\n");
// 		t_parenthesis *cmd = (t_parenthesis *)node->content;
// 		debug_print_tokens(cmd->redir_list);
// 		printTree(cmd->tree, level, "ROOT PARENTHESIS");
// 	}

// 	printTree(node->left, level + 1, "LEFT");
// 	printTree(node->right, level + 1, "RIGHT");
// }


