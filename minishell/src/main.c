/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/08 08:30:54 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Command commands[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"export", cmd_export},
	{NULL, NULL}
};

Commandenv commandsenv[] = {
	{"env", cmd_env},
	{NULL, NULL}
};

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
int main(void)
{
	print_header();
	char *input;

	CommandHistory* history = create_history();
	signal(SIGINT, handle_sigint);

	while (1)
	{
		char *username = getenv("USER");
		char *prompt = malloc(ft_strlen(username) + ft_strlen("@minimalianteo$ ") + 1);
		ft_strlcpy(prompt, username, ft_strlen(username)+ 1);
		ft_strlcat(prompt, "@minimalianteo$ ", ft_strlen(username) \
		+ ft_strlen("@minimalianteo$ ") + 1);
		input = readline(prompt);
		free(prompt);
		if (input && *input)
			add_history(input);
		if (input == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		if (ft_strcmp(input, "history") == 0)
		{
			printf("%s", cmd_history(history));
			free(input);
			continue;
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		parse_command(input, history);
		free(input);
	}
	return 0;
}
