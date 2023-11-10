/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:47:40 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/08 17:58:02 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swapstrings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	selection_sort(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcasecmp(array[i], array[j]) > 0)
				swapstrings(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}

char	*order_result(char *result)
{
	char	**result_matrix;
	char	*ret;
	int		i;

	result_matrix = ft_split(result, ' ');
	if (result == NULL)
		return (NULL);
	if (result_matrix == NULL)
		return (NULL);
	selection_sort(result_matrix);
	ret = NULL;
	i = 0;
	while (result_matrix[i] != NULL)
	{
		if (i > 0)
			ret = ft_strjoin2(ret, " ");
		ret = ft_strjoin2(ret, result_matrix[i]);
		i++;
	}
	i = 0;
	while (result_matrix[i] != NULL)
		free(result_matrix[i++]);
	free(result);
	free(result_matrix);
	return (ret);
}

void	close_free_dir(struct dirent *entry, char *dirname, DIR *dir)
{
	free(entry);
	free(dirname);
	closedir(dir);
}

void	open_read_getcwd(char **dirname, DIR **dir, struct dirent **entry)
{
	*dirname = getcwd(0, 0);
	*dir = opendir(*dirname);
	*entry = readdir(*dir);
}
