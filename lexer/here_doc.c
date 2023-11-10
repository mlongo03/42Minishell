/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:54:01 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 15:54:18 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*start_back(t_list *here_doc_lst)
{
	while (here_doc_lst && here_doc_lst->prev)
		here_doc_lst = here_doc_lst->prev;
	return (here_doc_lst);
}

void	*handle_list_heredocs(int op)
{
	static t_list	*here_doc_lst;
	t_list			*res;
	char			*here_doc;

	if (op == START)
	{
		here_doc_lst = start_back(here_doc_lst);
		ft_lstclear(&here_doc_lst, &del);
		here_doc_lst = NULL;
	}
	else if (op == ADD)
	{
		here_doc = here_doc_name();
		ft_lstadd_back(&here_doc_lst, ft_lstnew(here_doc));
		return (here_doc);
	}
	else if (op == LIST)
		return (start_back(here_doc_lst));
	else if (op == GET)
	{
		res = here_doc_lst;
		if (here_doc_lst->next)
			here_doc_lst = here_doc_lst->next;
		return (res->content);
	}
	return (NULL);
}

void	handle_here_doc_sig(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

int	reading(int fd, char *del, t_mini *mini)
{
	char	*str;

	signal(SIGINT, handle_here_doc_sig);
	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
		{
			printf("\n");
			free(str);
			free(del);
			exit(0);
		}
		if (ft_strcmp(str, del) == 0)
			break ;
		str = expander(mini, str);
		write(fd, str, ft_strlen(str));
		write(fd, &"\n", 1);
		free(str);
	}
	free(str);
	free(del);
	exit(0);
}

void	handle_here_doc(char *del, t_mini *mini)
{
	char	*here_doc;
	int		fd;
	int		pid;
	int		exit_status;

	here_doc = handle_list_heredocs(ADD);
	fd = open(here_doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		reading(fd, del, mini);
	waitpid(pid, &exit_status, 0);
	free(del);
	g_last_exit_status_cmd = WEXITSTATUS(exit_status);
	close(fd);
}

char	*create_del(char *s)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			while (s[i] && s[i] != quote)
				i++;
			break ;
		}
		i++;
	}
	return (ft_substr(s, 0, i));
}

void	del(void *str)
{
	free(str);
}
