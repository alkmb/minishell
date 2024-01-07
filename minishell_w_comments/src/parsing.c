/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/01/07 17:24:21 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parse_command(char *input, CommandHistory* history)
{
	//AÑADIMOS AL HISTORIAL LA STRING DEL COMANDO
	//(el del main es en caso de que no se ejecute ningun comando).
	add_to_history(history, input);

	int i = 0;
	// 7 ES EL MAXIMO DE COMANDOS QUE HAY EN EL SUBJECT ASI QUE NO ME COMPLICO MAS
	char *commands[7];

	//SEPARAMOS LOS COMANDOS POR EL PIPE
	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	//LLAMAMOS A LA FUNCION QUE SE ENCARGA DE EJECUTAR LOS COMANDOS
	chose_command(commands, i - 1);
}

void chose_command(char *commands[], int n)
{
	if (n < 0)
		return;
	//SI SOLO HAY UN COMANDO
	if (n == 0)
	{
		char *args[MAX_ARGS];
		int i = 0;
		//SEPARAMOS LOS ARGUMENTOS POR EL ESPACIO PARA PODER EJECUTARLOS
		//CON SUS RESPECTIVAS INSTRUCCIONES (EJ. "cd ..", "echo hola")
		args[i] = ft_strtok(commands[n], " ");
		while (args[i] != NULL) {
			i++;
			args[i] = ft_strtok(NULL, " ");
		}
		//EJECUTAMOS LOS COMANDOS
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		return;
	}
	else
		//SI HAY MAS DE UN COMANDO LLAMAMOS A LA FUNCION QUE SE ENCARGA DE LOS PIPES
		handle_pipes(commands, n);
}

void single_command(char *args[], int fd[])
{
	//SI SOLO HAY UN COMANDO
	dup2(fd[1], STDOUT_FILENO); //redirigimos la salida estandar al pipe
	close(fd[0]); //cerramos la entrada del pipe
	close(fd[1]); //cerramos la salida del pipe
	//EJECUTAMOS LOS COMANDOS
	execute_builtin_commandenv(args, environ);
	execute_builtin_command(args);
	exit(EXIT_SUCCESS);
}

void chose_pipe(char *commands[], int n)
{
	int i = 0;
	pid_t pid;
	int fd[2];
	int fd_in = 0;

	//SI HAY MAS DE UN COMANDO
	while(i <= n)
	{
		//CREAMOS EL PIPE
		pipe(fd);
		//CREAMOS EL HIJO
		pid = fork();
		//SI ES EL HIJO
		if (pid == 0)
		{
			//REDIRIGIMOS LA ENTRADA Y SALIDA ESTANDAR
			if (fd_in != 0)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			//REDIRIGIMOS LA SALIDA ESTANDAR AL PIPE
			if (i != n)
				dup2(fd[1], STDOUT_FILENO); //redirigimos la salida estandar al pipe
			close(fd[0]); //cerramos la entrada del pipe
			close(fd[1]); //cerramos la salida del pipe
			char *args[MAX_ARGS];
			int j = 0;
			char *saveptr; //para el strtok_r
			//SEPARAMOS LOS ARGUMENTOS POR EL ESPACIO PARA PODER EJECUTARLOS
			// (lo mismo que antes)
			args[j] = ft_strtok_r(commands[i], " ", &saveptr);
			while (args[j] != NULL)
				args[++j] = ft_strtok(NULL, " ");
			//EJECUTAMOS LOS COMANDOS
			execute_builtin_commandenv(args, environ);
			execute_builtin_command(args);
			exit(EXIT_SUCCESS);
		}
		//SI ES EL PADRE
		else
		{
			wait(NULL); //esperamos a que termine el hijo
			if (fd_in != 0) //si no es el primer comando
				close(fd_in); //cerramos la entrada del pipe
			fd_in = fd[0]; //guardamos la entrada del pipe
			close(fd[1]); //cerramos la salida del pipe
		}
		i++;
	}
}

void handle_pipes(char *commands[], int n)
{
	char *args[MAX_ARGS];
	int fd[2];
	pid_t pid;
	int i = 0;
	char *saveptr;

	//SEPARAMOS LOS ARGUMENTOS POR EL ESPACIO PARA PODER EJECUTARLOS
	//(lo mismo xdxdxddxd)
	args[i] = ft_strtok_r(commands[n], " ", &saveptr);
	while (args[i] != NULL)
		args[++i] = ft_strtok(NULL, " ");
	if (pipe(fd) == -1)
		perror("Error creating pipe");
	//CREAMOS EL HIJO
	pid = fork();
	//SI ES EL HIJO Y SOLO HAY UN COMANDO
	if (pid == 0 && args[1] == NULL)
		single_command(args, fd);
	//SI ES EL HIJO Y HAY MAS DE UN COMANDO
	else
		chose_pipe(commands, n);
	//SI ES EL PADRE
	close(fd[0]); //cerramos la entrada del pipe
	close(fd[1]); //cerramos la salida del pipe
	waitpid(pid, NULL, 0); //esperamos a que termine el hijo
}
