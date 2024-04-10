/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/04/10 02:04:36 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_header(void)
{
	char	*header;

	header = "\033[1;31m" \
	"███╗   ███╗██╗███╗   ██╗██╗\n" \
	"████╗ ████║██║████╗  ██║██║\n" \
	"██╔████╔██║██║██╔██╗ ██║██║\n" \
	"██║╚██╔╝██║██║██║╚██╗██║██║\n" \
	"██║ ╚═╝ ██║██║██║ ╚████║██║\n" \
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝\n" \
	"\n" \
	"███╗   ███╗ █████╗ ██╗   ██╗ █████╗ ███╗   ██╗██████╗███████╗ ██████╗\n" \
	"████╗ ████║██╔══██╗██║   ██║██╔══██╗████╗  ██║╚═██╔═╝██╔════╝██╔═══██╗\n" \
	"██╔████╔██║███████║██║   ██║███████║██╔██╗ ██║  ██║  █████╗  ██║   ██║\n" \
	"██║╚██╔╝██║██╔══██║██║   ██║██╔══██║██║╚██╗██║  ██║  ██╔══╝  ██║   ██║\n" \
	"██║ ╚═╝ ██║██║  ██║█████╗██║██║  ██║██║ ╚████║  ██║  ███████╗╚██████╔╝\n" \
	"╚═╝     ╚═╝╚═╝  ╚═╝╚════╝╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝  ╚═╝  ╚══════╝ ╚═════╝\n" \
	"\n" \
	"& CACHETEO SHELL.\n" \
	"\033[0m";
	ft_printf("\n%s\n", header);
}

char	*create_prompt(void)
{
	char	*username;
	char	*prompt;

	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	prompt = malloc(ft_strlen(username) + ft_strlen("@minimalianteo$ ") + 1);
	ft_strlcpy(prompt, username, ft_strlen(username)+ 1);
	ft_strlcat(prompt, "@minimalianteo$ ", ft_strlen(username) \
	+ ft_strlen("@minimalianteo$ ") + 1);
	return (prompt);
}

void	handle_sigint(int sig)
{
	char	*new_prompt;

	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		new_prompt = create_prompt();
		rl_set_prompt(new_prompt);
		free(new_prompt);
		rl_redisplay();
	}
}

int	main(void)
{
	char				*input;
	char				*prompt;
	int					status;
	t_commandhistory	*history;

	signal(SIGINT, handle_sigint);
	history = create_history();
	print_header();
	status = 0;
	while (1)
	{
		prompt = create_prompt();
		input = readline(prompt);
		free(prompt);
		if (input && *input)
			add_history(input);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (ft_strncmp(input, "echo $?", 8) == 0)
			ft_printf("minimalianteo: %d\n", status);
		status = parse_command(input, history);
		free(input);
	}
	return (0);
}
