/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/18 07:39:29 by kmb              ###   ########.fr       */
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

void handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	ft_printf("%d\n", sig);
}

void print_header(void)
{
	char *header =
	"\033[1;31m" // Set the text to the color red
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
	"\033[0m"; // Reset the text color to default
	ft_printf("\n%s\n", header);
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
			exit(0);
		if (ft_strcmp(input, "history") == 0)
		{
			printf("%s", cmd_history(history));
			free(input);
			continue;
		}
		parse_command(input, history);
		free(input);
	}
	return 0;
}
