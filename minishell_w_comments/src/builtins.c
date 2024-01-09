/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/08 08:30:08 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// COMANDO ECHO QUE IMPRIME LO QUE LE PASES
void cmd_echo(char **args)
{
	int i = 1;
	while (args[i] != NULL)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("\n");
}

// COMANDO CD QUE CAMBIA DE DIRECTORIO (literal el chdir lo hace todo)
void cmd_cd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
		{
			perror(args[1]);
		}
	}
	// SI NO SE LE PASA NADA CAMBIA AL HOME Y CREO QUE ESTO NO HACE FALTA
	else
		chdir(getenv("HOME"));
}

// COMANDO PWD QUE IMPRIME EL DIRECTORIO ACTUAL
void cmd_pwd(void)
{
	char cwd[1024];
	//LO MISMO QUE EL CD EL  getcwd LO HACE TODO
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

// COMANDO UNSET QUE ELIMINA UNA VARIABLE DE ENTORNO
void cmd_unset(char **args)
{
	if (args[1] != NULL)
	{
		int i = 0;
		//RECORREMOS EL ARRAY DE ENV
		while (environ[i])
		{
			//SI LA VARIABLE ES IGUAL A LA QUE ESTAMOS BUSCANDO Y EL SIGUIENTE CARACTER ES UN =
			if (ft_strncmp(environ[i], args[1], ft_strlen(args[1])) == 0 \
				&& environ[i][ft_strlen(args[1])] == '=')
			{
				//LA ELIMINAMOS
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				break;
			}
			i++;
		}
	}
	// MENSAJE DE ERROR SI NO SE LE PASA NADA
	else
		ft_printf("Usage: unset variable_name\n");
}

// COMANDO EXPORT QUE IMPRIME TODAS LAS VARIABLES DE ENTORNO
void cmd_export(char **args)
{
	if (args[1] == NULL)
	{
		//RECORREMOS EL ARRAY DE ENV
		char **env = environ;
		while(*env != NULL)
		{
			//IMPRIMIMOS LAS VARIABLES DE ENTORNO CON EL FORMATO DE EXPORT
			ft_printf("declare -x %s\n", *env);
			env++;
		}
	}
}
