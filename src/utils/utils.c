/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:25:19 by kmb               #+#    #+#             */
/*   Updated: 2024/04/12 22:25:42 by kmb              ###   ########.fr       */
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