/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:51:32 by akambou           #+#    #+#             */
/*   Updated: 2024/04/25 12:16:39 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_unset(t_shell *shell)
{
	int	index;

	if (shell->data->args[1] != NULL)
	{
		index = find_env_var(shell);
		if (index != -1)
			unset_env_var(shell, index);
	}
	else
	{
		ft_printf("unset: not enough arguments\n");
		return (127);
	}
	return (0);
}

void	cmd_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->environ[i] != NULL)
	{
		ft_printf("%s\n", shell->environ[i]);
		i++;
	}
}

int	cmd_export(t_shell *shell)
{
	int		i;
	int		j;

	i = 1;
	if (shell->data->args[i] == NULL)
	{
		j = 0;
		while (shell->environ[j] != NULL)
		{
			printf("declare -x %s\n", shell->environ[j]);
			j++;
		}
		return (0);
	}
	else
		add_to_environment(shell);
	return (0);
}
