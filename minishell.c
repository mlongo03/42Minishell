/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/10 15:28:00 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status_cmd = 0;

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

void	free_tokens(t_token *token_lst)
{
	t_token			*tmp;
	t_declaration	*type_decl;
	t_declaration	*tmpdecl;
	char			**args;
	int				i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->token == OPERATOR || token_lst->token == OUT_FILE_APPEND || token_lst->token == OUT_FILE_TRUNC
			|| token_lst->token == IN_FILE_TRUNC || token_lst->token == OPERATOR || token_lst->token == CMD_NAME)
			free(token_lst->value);
		else if (token_lst->token == ENV_VAR_DECL
			|| token_lst->token == ENV_VAR_UNSET)
		{
			type_decl = (t_declaration *)token_lst->value;
			while (type_decl)
			{
				tmpdecl = type_decl;
				if (tmpdecl->name)
					free(tmpdecl->name);
				if (tmpdecl->value)
					free(tmpdecl->value);
				type_decl = type_decl->next;
				free(tmpdecl);
			}
		}
		else if (token_lst->token == CMD_ARG)
		{
			i = 0;
			args = (char **)token_lst->value;
			while (args[i])
			{
				free(args[i]);
				i++;
			}
			free(args);
		}
		tmp = token_lst;
		token_lst = token_lst->next;
		free(tmp);
	}
	free(token_lst);
}

void	free_tree(t_tree *tree)
{
	t_parenthesis	*par;
	t_simple_cmd	*simple_cmd;

	if (!tree)
		return ;
	if (tree->type == PARENTHESI)
	{
		par = (t_parenthesis *)tree->content;
		free_tokens((t_token *)par->redir_list);
		free_tree((t_tree *)par->tree);
		free(par);
	}
	else if (tree->type == SIMPLE_CMD)
	{
		simple_cmd = (t_simple_cmd *)tree->content;
		free_tokens(simple_cmd->redir_list);
		free(simple_cmd->env);
		if (simple_cmd->cmd)
		{
			free(simple_cmd->cmd->cmd_arg);
			free_tokens(simple_cmd->cmd->cmd_name);
			free(simple_cmd->cmd);
		}
		free(simple_cmd);
	}
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

void	ft_free_all(t_token *token_lst, t_tree *tree)
{
	free_tokens(token_lst);
	free_tree(tree);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_last_exit_status_cmd = EXIT_FAILURE;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGTERM)
		exit (1);
}

void	ign(int signum)
{
	if (signum)
		;
}

void	*var_container(t_token *token_lst, t_tree *tree, t_mini *mini, int op)
{
	static t_token	*this_token_lst;
	static t_tree	*this_tree;
	static t_mini	*this_mini;

	if (op == SET)
	{
		this_token_lst = token_lst;
		this_tree = tree;
		this_mini = mini;
		return (NULL);
	}
	else if (op == GET_TREE)
		return (this_tree);
	else if (op == GET_TOKENS)
		return (this_token_lst);
	else if (op == GET_MINI)
		return (this_mini);
	return (NULL);
}

int	ft_isredirection(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

char	**wildcard_split(char **splitcmd, t_mini *mini)
{
	int		i;
	int		j;
	char	*tmp;
	char	*expanded;
	char	**split_expanded;
	int		end;
	int		end_new;

	i = 0;
	j = 0;
	while (splitcmd[i])
	{
		expanded = ft_wildcard(splitcmd[i], mini);
		split_expanded = ft_split(expanded, ' ');
		if (split_expanded[1])
		{
			if (i != 0 && ft_isredirection(splitcmd[i - 1]))
			{
				free_matrix(split_expanded);
				splitcmd[i] = expanded;
			}
			else
			{
				end = env_rows(splitcmd) - 1;
				splitcmd = ft_realloc(splitcmd, sizeof(char *), env_rows(splitcmd), env_rows(splitcmd) + env_rows(split_expanded));
				end_new = env_rows(splitcmd) + env_rows(split_expanded) - 3 - i;
				while (end > i)
					splitcmd[end--] = splitcmd[end_new--];
				tmp = splitcmd[i];
				while (split_expanded[j])
					splitcmd[i++] = split_expanded[j++];
				free(expanded);
				free(split_expanded);
			}
		}
		else
		{
			free_matrix(split_expanded);
			splitcmd[i] = expanded;
		}
		if (splitcmd[i])
			i++;
	}
	return (splitcmd);
}

void	free_env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
		free(mini->env[i++]);
	free(mini->env);
	free(mini);
}

void	increment_shlvl(t_mini *mini)
{
	char	*shlvl;
	int		i;
	int		j;
	char	*num;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], "SHLVL=", ft_strlen("SHLVL=")))
		{
			shlvl = ft_strdup(mini->env[i]);
			free(mini->env[i]);
			j = ft_atoi(&shlvl[ft_strlen("SHLVL=")]);
			j++;
			free(shlvl);
			num = ft_itoa(j);
			mini->env[i] = ft_strjoin("SHLVL=", num);
			free(num);
			return ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**splitcmd;
	char	*fixed;
	t_token	*token_list;
	t_tree	*tree;
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	copy_env(envp, mini);
	token_list = NULL;
	increment_shlvl(mini);
	while (1)
	{
		unlink_here_docs(handle_list_heredocs(LIST));
		handle_list_heredocs(START);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		str = readline("Minishell> ");
		if (str == NULL)
		{
			printf("\n");
			free(str);
			free_env(mini);
			exit(0);
		}
		add_history(str);
		fixed = fix_syntax(str);
		free(str);
		// if (!check(fixed, mini))
		// {
		// 	free(fixed);
		// 	if (g_last_exit_status_cmd == 130)
		// 		continue ;
		// 	printf("Syntax error\n");
		// 	g_last_exit_status_cmd = 2;
		// 	continue ;
		// }
		splitcmd = ft_split(fixed, ' ');
		free(fixed);
		splitcmd = wildcard_split(splitcmd, mini);
		token_list = tokenizer(splitcmd, mini);
		if (token_list)
			while (token_list->next)
				token_list = token_list->next;
		tree = tree_create(token_list, OP);
		if (token_list)
			while (token_list->prev)
				token_list = token_list->prev;
		mini->splitcmd = splitcmd;
		var_container(token_list, tree, mini, SET);
		execute(tree, STDIN_FILENO, STDOUT_FILENO, mini);
		free_matrix(splitcmd);
		ft_free_all(token_list, tree);
	}
}
