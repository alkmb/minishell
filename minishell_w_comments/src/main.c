/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/07 17:41:19 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ASIGNANDO LAS FUNCIONES DE CADA COMANDO A SUS RESPECTIVO NOMBRES
Command commands[] = {
	{"echo", cmd_echo},
	{"rev", cmd_rev},
	{"ls", cmd_ls},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"export", cmd_export},
	{NULL, NULL}
};
// LA DE ENV VA SEPARADA PORQUE SE LLAMA CON PARAMETROS DISTINTOS
Commandenv commandsenv[] = {
	{"env", cmd_env},
	{NULL, NULL}
};
// LITERALMENTE EL HEADER NO TIENE MUCHO
void print_header(void)
{
		char *header = "  ####       ####\n\
 #####     ######   ##             ##\n\
 ##  ###  ###  ##\n\
 ##    ###     ##   ##   ########  ##   @   @   ###\
    #    !   ###   @#  $   ===   @##   #$$#\n\
 ##            ##   ##   ##    ##  ##   # v #   @ #\
    #    !   ! #   # # #    !    @     #  #\n\
 ##            ##   ##   ##    ##  ##   $ ! #   #=@\
    #    !   #=@   !  !#    !    @=    #  #\n\
 ##            ##   ##   ##    ##  ##   #   #   # #\
    ##   !   # #   #   #    !    @##   ###$\n";
	ft_printf("\n%s\n", header);
}
// EL MAIN Y SUS COSAS(NO SON POCAS)
int main(void)
{
	print_header();
	char *input;
	//LLAMMA A LA FUNCION QUE CREA EL HISTORIAL
	CommandHistory* history = create_history();
	signal(SIGINT, handle_sigint);
	// EL LOOP QUE SE REPITE HASTA QUE SE CIERRE EL SHELL
	while (1)
	{
		// EL PROMPT
		char *username = getenv("USER");
		char *prompt = malloc(ft_strlen(username) + ft_strlen("@minimalianteo$ ") + 1);
		ft_strlcpy(prompt, username, ft_strlen(username)+ 1);
		ft_strlcat(prompt, "@minimalianteo$ ", ft_strlen(username) \
		+ ft_strlen("@minimalianteo$ ") + 1);
		// EL READLINE PARA LEER EL INPUT
		input = readline(prompt);
		free(prompt);
		// AGREGA EL INPUT AL HISTORIAL
		if (input && *input)
			add_history(input);
		// SI NO HAY INPUT, SALE DEL SHELL
		if (input == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		// SI EL INPUT ES EL HISTOIAL SE LLAMA A LA FUNCION("history.c")
		if (ft_strcmp(input, "history") == 0)
		{
			printf("%s", cmd_history(history));
			free(input);
			continue;
		}
		// SI EL INPUT ES EXIT, SALE DEL SHELL
		else if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		// SI NO, SE LLAMA A LA FUNCION QUE SEPARA EL INPUT EN COMANDOS("parsing.c")
		parse_command(input, history);
		free(input);
	}
	// RETURN 0 xdddd
	return 0;
}
