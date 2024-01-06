/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 13:13:38 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_builtin_command(char **args)
{
	int i = 0;

	while (commands[i].name != NULL)
	{
		if (ft_strcmp(args[0], commands[i].name) == 0)
		{
			commands[i].func(args);
			return;
		}
		i++;
	}
}

void execute_builtin_commandenv(char **args, char **environ)
{
	int i = 0;

	while ( commandsenv[i].name != NULL)
	{
		if (ft_strcmp(args[0], commandsenv[i].name) == 0)
		{
			commandsenv[i].func(environ);
			return;
		}
		i++;
	}
}
