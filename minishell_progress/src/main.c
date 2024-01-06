/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 12:26:34 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Command commands[] = {
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
	printf("%d\n", sig);
	printf("%s@minimalianteo$ ", getenv("USER"));
	fflush(stdout);
}

int main(void)
{
	signal(SIGINT, handle_sigint);

	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("%s@minimalianteo$ ", getenv("USER"));
		read = getline(&input, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				exit(0);
			}
			else
				perror("Error reading input");
			free(input);
			break;
		}
		if (input[read - 1] == '\n')
			input[read - 1] = '\0';
		parse_command(input);
		free(input);
		input = NULL;
	}
	return 0;
}
