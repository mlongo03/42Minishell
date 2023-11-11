/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_word_control.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:46:42 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 18:37:13 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_filter_return(char *filter)
{
	free(filter);
	return (0);
}

int	wildcard_filters(t_filter *filter_struct, int *y, int i, char *input)
{
	if (!input[i])
	{
		if (!word_end_filter(filter_struct->filter, filter_struct->filename, y))
			return (0);
	}
	else if (i != 0 && !check_wildcard_before(input, i - 1))
	{
		if (!word_start_filter(filter_struct->filter,
				filter_struct->filename, y))
			return (0);
	}
	else
	{
		if (!word_middle_filter(filter_struct->filter,
				filter_struct->filename, y))
			return (0);
	}
	return (1);
}

int	filter_word(char *input, char *filename, t_mini *mini)
{
	int			i;
	int			y;
	t_filter	filter_struct;

	i = 0;
	y = -1;
	filter_struct.filename = filename;
	while (input[i])
	{
		i += move_to_wildcard(&input[i]);
		if (i != 0 && input[i - 1] != '*')
		{
			filter_struct.filter = expand_strbefore(input, i - 1, mini);
			if (!wildcard_filters(&filter_struct, &y, i, input))
				return (free_filter_return(filter_struct.filter));
			if (input[i] == '*')
				i++;
			free(filter_struct.filter);
		}
		else
			i++;
	}
	return (1);
}
