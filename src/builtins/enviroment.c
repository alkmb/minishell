/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:20:03 by akambou           #+#    #+#             */
/*   Updated: 2024/04/17 16:10:44 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_environment(char **env)
{
	while (*env != NULL)
	{
		ft_printf("declare -x %s\n", *env);
		env++;
	}
}

int	find_env_var(t_shell *shell)
{
	int		i;
	char	*name;
	char	*env_var;

	i = 0;
	while (shell->environ[i])
	{
		env_var = ft_strdup(shell->environ[i]);
		name = ft_strtok(env_var, "=");
		if (ft_strcmp(name, shell->data->args[1]) == 0)
		{
			free(env_var);
			return (i);
		}
		free(env_var);
		i++;
	}
	return (-1);
}

void	unset_env_var(t_shell *shell, int index)
{
	int		j;
	char	*tmp;

	j = index;
	tmp = shell->environ[j];
	while (shell->environ[j])
	{
		shell->environ[j] = shell->environ[j + 1];
		j++;
	}
	free(tmp);
}
