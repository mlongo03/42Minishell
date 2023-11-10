/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:54:06 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/09 15:34:01 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_mat(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

char	*ft_strndup(char *str, int start, int finish)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc((finish - start) + 1, 1);
	while (start < finish)
	{
		ret[i] = str[start];
		i ++ ;
		start ++;
	}
	ret[i] = 0;
	return (ret);
}

char	**split_bt_nt_t_mc(char *str, char c)
{
	int		i;
	char	**mat;

	i = -1;
	mat = (char **)malloc(3 * sizeof(char *));
	for (i = 0; i < 3; i++)
		mat[i] = NULL;
	if (ft_strchr(str, '=') != 0)
	{
		while (str[++i] != '=')
			;
		mat[0] = ft_substr(str, 0, i);
		mat[1] = ft_substr(str, i + 1, ft_strlen(str));
		mat[2] = NULL;
		return (mat);
	}
	if (ft_strchr(str, c) != 0)
	{
		mat[1] = ft_strdup(str);
		mat[2] = 0;
	}
	return (mat);
}
