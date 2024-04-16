/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/04/16 21:29:14 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_echo(t_shell *shell)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (shell->data->args[i] != NULL && ft_strcmp(shell->data->args[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (shell->data->args[i] != NULL)
	{
		if (ft_strcmp(shell->data->args[i], "$?") == 0)
			ft_printf("%d", shell->status);
		else
		{
			ft_printf("%s", shell->data->args[i]);
			if (shell->data->args[i + 1] != NULL)
				ft_printf(" ");
		}
		i++;
	}
	if (!newline && ft_strcmp(shell->data->args[0], "$?") != 0)
		ft_printf("\n");
	return (0);
}

int	cmd_cd(t_shell *shell)
{
	char	*path;

	if (shell->data->args[1] != NULL)
	{
		if (shell->data->args[1][0] == '~')
		{
			path = malloc(ft_strlen(getenv("HOME")) + strlen(shell->data->args[1]));
			ft_strlcpy(path, getenv("HOME"), 5);
			ft_strlcat(path, shell->data->args[1] + 1, ft_strlen(getenv("HOME")) \
			+ ft_strlen(shell->data->args[1]) + 1);
		}
		else
			path = shell->data->args[1];
		if (chdir(path) != 0)
		{
			if (shell->data->args[1][0] == '~')
				free(path);
			return (127);
		}
		if (shell->data->args[1][0] == '~')
			free(path);
	}
	else
		chdir(getenv("HOME"));
	return (0);
}

int	cmd_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (127);
	}
	return (0);
}
