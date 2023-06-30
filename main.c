/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:12:32 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/30 15:11:49 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static int	ft_free(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}

static int	allocate(size_t *j, int *x, char ***split, int l)
{
	int	i;

	i = 0;
	*j = 0;
	*x = -1;
	*split = (char **) malloc(l * sizeof(char *));
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (s == NULL)
		return (NULL);
	i = allocate(&j, &index, &split, count_words(s, c) + 1);
	if (split == NULL)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	res[ft_strlen(s1) + ft_strlen(s2)] = 0;
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		res[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	return (res);
}



int	cmd_name(char *str)
{
	int i;
	char	**path;
	char	*strjoin;
	char	*tmp;

	i = -1;
	if (!strcmp(str, "pwd") || !strcmp(str, "echo") || !strcmp(str, "cd")
		|| !strcmp(str, "exit") || !strcmp(str, "env")
		|| !strcmp(str, "unset") || !strcmp(str, "export"))
		return(1);
	path = ft_split(getenv("PATH"), ':');
	if (!access(str, F_OK | R_OK))
		return (1);
	while (path[++i])
	{
		strjoin = ft_strjoin(path[i], "/");
		tmp = strjoin;
		strjoin = ft_strjoin(strjoin, str);
		free(tmp);
		if (!access(strjoin, F_OK | R_OK))
		{
			ft_free(path);
			free(strjoin);
			return (1);
		}
		free(strjoin);
	}
	ft_free(path);
	return (0);
}

void	parser(char **splitcmd)
{
	int i;
	int expected_cmd_name;
	int expected_cmd_arg;

	i = 0;
	expected_cmd_name = 1;
	expected_cmd_arg = 0;
	while (splitcmd[i])
	{
		if (!strcmp(splitcmd[i], ")"))
		{

		}
		if (!strcmp(splitcmd[i], "("))
		{

		}
		else if (!strcmp(splitcmd[i], "<"))
		{
			printf("redirect_input file_input ");
			i++;
		}
		else if (!strcmp(splitcmd[i], ">"))
		{
			printf("redirect_output_trunc file_output_trunc ");
			i++;
		}
		else if (!strcmp(splitcmd[i], "<<"))
		{
			printf("here_doc delimiter ");
			i++;
		}
		else if (!strcmp(splitcmd[i], ">>"))
		{
			printf("redirect_output_append file_output_append ");
			i++;
		}
		else if (cmd_name(splitcmd[i]) && expected_cmd_name && !expected_cmd_arg)
		{
			printf("cmd_name ");
			expected_cmd_name = 0;
			expected_cmd_arg = 1;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "&&") && !expected_cmd_name)
		{
			printf("AND ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "||") && !expected_cmd_name)
		{
			printf("OR ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "|") && !expected_cmd_name)
		{
			printf("PIPE ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (!expected_cmd_name && expected_cmd_arg)
			printf("cmd_arg ");
		else
		{
			printf("minishell: %s: command not found\n", splitcmd[i]);
			return ;
		}
		i++;
	}
	printf("\n");
}

int main()
{
	char *str;
	char **splitcmd;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		splitcmd = ft_split(str, ' ');
		parser(splitcmd);
		ft_free(splitcmd);
		free(str);
	}
}
