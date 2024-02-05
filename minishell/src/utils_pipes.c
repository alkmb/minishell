/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:14:07 by akambou           #+#    #+#             */
/*   Updated: 2024/02/05 04:29:20 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(int *i, int *fd_in)
{
	*fd_in = 0;
	*i = 0;
}

void	handle_builtin_commands(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cmd_cd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		cmd_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		cmd_unset(args);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

void	free_args(char **args)
{
	int	j;

	j = 0;
	while (args[j] != NULL)
		free(args[j++]);
	free(args);
}
