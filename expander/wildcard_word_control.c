/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_word_control.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:46:42 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/08 13:03:22 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_filter_return(char *filter)
{
	free(filter);
	return (0);
}

int	filter_word(char *input, char *filename, t_mini *mini)
{
	int		i;
	int		y;
	char	*filter;

	i = 0;
	y = -1;
	while (input[i])
	{
		i += move_to_wildcard(&input[i]);
		if (i != 0 && input[i - 1] != '*')
			filter = expand_strbefore(input, i - 1, mini);
		else
		{
			i++;
			continue ;
		}
		if (!input[i])
		{
			if (!word_end_filter(filter, filename, &y))
				return (free_filter_return(filter));
		}
		else if (i != 0 && !check_wildcard_before(input, i - 1))
		{
			if (!word_start_filter(filter, filename, &y))
				return (free_filter_return(filter));
		}
		else
		{
			if (!word_middle_filter(filter, filename, &y))
				return (free_filter_return(filter));
		}
		if (input[i] == '*')
			i++;
		free(filter);
	}
	return (1);
}

int	word_end_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = ft_strlen(filename) - 1;
	filter_index = ft_strlen(filter) - 1;
	while (filename_index != -1 && filter_index != -1 && filename_index >= *i)
	{
		if (filename[filename_index] != filter[filter_index])
			return (0);
		filename_index--;
		filter_index--;
	}
	if (filename_index >= *i || filename_index == -1 || filter_index == -1)
		return (1);
	else
		return (0);
}

int	word_start_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = 0;
	filter_index = 0;
	while (filename[filename_index] && filter[filter_index])
	{
		if (filename[filename_index] != filter[filter_index])
			return (0);
		filename_index++;
		filter_index++;
	}
	if ((!filename[filename_index] && !filter[filter_index])
		|| (filename[filename_index] && !filter[filter_index]))
	{
		*i = filename_index;
		return (1);
	}
	else
		return (0);
}

int	word_middle_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = *i;
	filter_index = 0;
	while (filename[filename_index] && filter[filter_index])
	{
		while ((filename[filename_index] && filter[filter_index])
			&& filename[filename_index++] == filter[filter_index++])
		{
		}
		if (!filter[filter_index])
			break ;
		else
			filter_index = 0;
		filename_index++;
	}
	if ((!filename[filename_index] && !filter[filter_index])
		|| (filename[filename_index] && !filter[filter_index]))
	{
		*i = filename_index;
		return (1);
	}
	else
		return (0);
}
