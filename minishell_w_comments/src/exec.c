/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/07 17:27:24 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// EJECTUA LOS COMANDOS BUILTINS EXCEPTO ENV
void execute_builtin_command(char **args)
{
	int i = 0;

	//RECORREMOS EL ARRAY DE COMANDOS BUILTINS
	while (commands[i].name != NULL)
	{
		//SI EL COMANDO ES IGUAL AL QUE ESTAMOS BUSCANDO
		if (ft_strcmp(args[0], commands[i].name) == 0)
		{
			//LO EJECUTAMOS
			commands[i].func(args);
			return;
		}
		i++;
	}
}

// EJECUTA EL COMANDO ENV
void execute_builtin_commandenv(char **args, char **environ)
{
	int i = 0;

	//RECORREMOS EL ARRAY DE COMANDOS BUILTINS
	while ( commandsenv[i].name != NULL)
	{
		// BUENO YA LO VAS PILLANDO NO?
		if (ft_strcmp(args[0], commandsenv[i].name) == 0)
		{
			commandsenv[i].func(environ);
			return;
		}
		i++;
	}
}

// COMANDO ENV
void cmd_env(char **environ)
{
	char *env_var = *environ; // *environ ES ENVIROMENTAL VARIABLE
	while (env_var != NULL)
	{
		ft_printf("%s\n", env_var);
		env_var = *(environ++);
	}
}

// SEÑALES XDDDD ME CAGO EN DIOS
void handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	ft_printf("%d\n", sig);
}
