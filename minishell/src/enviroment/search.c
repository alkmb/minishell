/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:20:03 by akambou           #+#    #+#             */
/*   Updated: 2024/05/05 18:48:01 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (index == -1)
		return ;
	j = index;
	tmp = shell->environ[j];
	if (!tmp)
		return ;
	while (shell->environ[j])
	{
		shell->environ[j] = shell->environ[j + 1];
		j++;
	}
	shell->environ[j] = tmp;
	shell->new_environ = malloc(sizeof(char *) * j);
	shell ->new_environ = ft_memcpy(shell->new_environ, \
	shell->environ, sizeof(char *) * j);
	tmp = NULL;
}
