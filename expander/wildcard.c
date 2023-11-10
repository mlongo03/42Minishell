/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:21:34 by alessiolong       #+#    #+#             */
/*   Updated: 2023/11/08 17:20:35 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_wildcard_before(char *input, int i)
{
	while (i != -1)
	{
		if (input[i] == '*')
			return (1);
		i--;
	}
	return (0);
}

int	is_wildcard_present(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '*')
			return (1);
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (input[i] && input[i] != quote)
				i++;
		}
		if (input[i])
			i++;
	}
	return (0);
}

int	move_to_wildcard(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '*')
			return (i);
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (input[i] && input[i] != quote)
				i++;
		}
		if (input[i])
			i++;
	}
	return (i);
}

char	*expand_strbefore(char *input, int i, t_mini *mini)
{
	int		len;
	int		start;
	char	*filter_to_expand;

	len = 0;
	start = i;
	while (start != -1 && input[start] != '*')
	{
		start--;
		len++;
	}
	filter_to_expand = malloc(len + 1);
	filter_to_expand[len] = 0;
	len--;
	start = i;
	while (len != -1 && input[i] != '*')
	{
		filter_to_expand[len] = input[i];
		len--;
		i--;
	}
	return (expander(mini, filter_to_expand));
}

char	*ft_wildcard(char *input, t_mini *mini)
{
	struct dirent	*entry;
	char			*dirname;
	char			*result;
	DIR				*dir;

	if (!is_wildcard_present(input))
		return (input);
	result = NULL;
	open_read_getcwd(&dirname, &dir, &entry);
	while ((entry))
	{
		if ((input[0] == '.' || entry->d_name[0] != '.')
			&& filter_word(input, entry->d_name, mini))
		{
			result = ft_strjoin2(result, entry->d_name);
			result = ft_strjoin2(result, " ");
		}
		entry = readdir(dir);
	}
	close_free_dir(entry, dirname, dir);
	if (result == NULL)
		return (input);
	free(input);
	return (order_result(result));
}
