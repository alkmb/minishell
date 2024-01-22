/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/21 06:05:57 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_header(void)
{
	char *header =
	"\033[1;31m"
	"███╗   ███╗██╗███╗   ██╗██╗\n"
	"████╗ ████║██║████╗  ██║██║\n"
	"██╔████╔██║██║██╔██╗ ██║██║\n"
	"██║╚██╔╝██║██║██║╚██╗██║██║\n"
	"██║ ╚═╝ ██║██║██║ ╚████║██║\n"
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝\n"
	"\n"
	"███╗   ███╗ █████╗ ██╗     ██╗ █████╗ ███╗   ██╗████████╗███████╗ ██████╗\n"
	"████╗ ████║██╔══██╗██║     ██║██╔══██╗████╗  ██║╚══██╔══╝██╔════╝██╔═══██╗\n"
	"██╔████╔██║███████║██║     ██║███████║██╔██╗ ██║   ██║   █████╗  ██║   ██║\n"
	"██║╚██╔╝██║██╔══██║██║     ██║██╔══██║██║╚██╗██║   ██║   ██╔══╝  ██║   ██║\n"
	"██║ ╚═╝ ██║██║  ██║███████╗██║██║  ██║██║ ╚████║   ██║   ███████╗╚██████╔╝\n"
	"\n"
	"& CACHETEO SHELL.\n"
	"\033[0m";
	ft_printf("\n%s\n", header);
}
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

void handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	ft_printf("%d\n", sig);
}
char	*create_prompt()
{
	char *username = getenv("USER");
	char *prompt = malloc(ft_strlen(username) + ft_strlen("@minimalianteo$ ") + 1);
	ft_strlcpy(prompt, username, ft_strlen(username)+ 1);
	ft_strlcat(prompt, "@minimalianteo$ ", ft_strlen(username) \
	+ ft_strlen("@minimalianteo$ ") + 1);
	return prompt;
}

int main(void)
{
	char *input;
	print_header();
	CommandHistory* history = create_history();
	signal(SIGINT, handle_sigint);

	while (1)
	{
		char *prompt = create_prompt();
		input = readline(prompt);
		free(prompt);
		if (input && *input)
			add_history(input);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (ft_strcmp(input, "history") == 0)
		{
			printf("%s", cmd_history(history));
			continue;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		parse_command(input, history);
		free(input);
		}
	return 0;
}
