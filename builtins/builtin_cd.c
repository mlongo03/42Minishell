/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/07 13:28:11 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_mini *mini)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
		{
			final_string = ft_strjoin("OLDPWD=", new_value);
			free(mini->env[i]);
			mini->env[i] = ft_strdup(final_string);
			free(final_string);
			break ;
		}
	}
	free(new_value);
}

void	update_pwd(t_mini *mini)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
		{
			final_string = ft_strjoin("PWD=", new_value);
			free(mini->env[i]);
			mini->env[i] = ft_strdup(final_string);
			free(final_string);
			break ;
		}
	}
	free(new_value);
}

int	ft_cd(char **command_line, t_mini *mini)
{
	char	*home;

	update_oldpwd(mini);
	home = getenv("HOME");
	if (command_line != NULL && !ft_strcmp(command_line[0], "$HOME"))
	{
		chdir(home);
		update_pwd(mini);
	}
	else if (!command_line)
	{
		chdir(home);
		update_pwd(mini);
	}
	else
	{
		if (chdir(command_line[0]))
		{
			printf("bash: cd: %s: No such file or directory", command_line[0]);
			return (1);
		}
		update_pwd(mini);
	}
	return (0);
}
