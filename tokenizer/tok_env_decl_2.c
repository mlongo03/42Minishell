/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_decl_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:39:38 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 16:39:51 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_decl_name(char *word)
{
	int		i;
	char	*err1;
	char	*err2;

	err1 = "=";
	err2 = "+=";
	i = 0;
	while (word[i] && word[i] != '=')
		i++;
	if (word[0] == '=')
		return (ft_substr(err1, 0, 1));
	else if (word[0] != '=' && word[i] == '=' && word[i - 1] == '+')
	{
		i--;
		if (word[0] == '+')
			return (ft_substr(err2, 0, 2));
	}
	else if (word[i] == 0)
		return (ft_substr(word, 0, ft_strlen(word)));
	return (ft_substr(word, 0, i));
}

char	*set_decl_value(char *word)
{
	int		start;
	int		end;
	char	*res;

	res = NULL;
	start = 0;
	end = 0;
	while (word[start] && word[start] != '=')
		start++;
	if (word[start] == 0)
		return (NULL);
	else if (word[start] == '=' && ft_isspace(word[start + 1]))
	{
		res = malloc(1);
		*res = 0;
		return (res);
	}
	start++;
	end = start;
	while (word[end])
		end++;
	return (ft_substr(word, start, end));
}

int	set_decl_mode(char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '=')
		i++;
	if (word[i] == '=' && word[i - 1] == '+')
		return (2);
	else if (word[i] == '=')
		return (1);
	else
		return (0);
}
