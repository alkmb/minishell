/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 17:05:02 by kmb              ###   ########.fr       */
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
    ##   !   # #   #   #    !    @##   ###$";
	ft_printf("%s\n", header);
}
int main(void)
{
	print_header();
	char *input;

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
		if (input == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		parse_command(input);
		free(input);
	}
	return 0;
}
