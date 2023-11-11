/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:35:59 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/10 18:42:10 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			&& filename[filename_index] == filter[filter_index])
		{
			filter_index++;
			filename_index++;
		}
		if (!filter[filter_index])
			break ;
		else
			filter_index = 0;
		filename_index++;
	}
	if (!((!filename[filename_index] && !filter[filter_index])
			|| (filename[filename_index] && !filter[filter_index])))
		return (0);
	*i = filename_index;
	return (1);
}
