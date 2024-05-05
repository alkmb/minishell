/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:25:19 by kmb               #+#    #+#             */
/*   Updated: 2024/05/05 14:47:17 by kmb              ###   ########.fr       */
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
	char	cwd[1024];

	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_strlcpy(cwd, "unknown", sizeof(cwd));
	prompt = malloc(ft_strlen(username) + ft_strlen("@") + ft_strlen(cwd) + ft_strlen("$ ") + 1);
	ft_strlcpy(prompt, username, ft_strlen(username) + 1);
	ft_strlcat(prompt, "@", ft_strlen(prompt) + ft_strlen("@") + 1);
	ft_strlcat(prompt, cwd, ft_strlen(prompt) + ft_strlen(cwd) + 1);
	ft_strlcat(prompt, "$ ", ft_strlen(prompt) + ft_strlen("$ ") + 1);
	return (prompt);
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(2, "Quit 3\n", 7);
		exit(130);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	handle_sigint(int sig)
// {
// 	static char	*new_prompt = NULL;

// 	if (sig == SIGINT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		if (new_prompt != NULL)
// 		{
// 			free(new_prompt);
// 			new_prompt = NULL;
// 		}
// 		new_prompt = create_prompt();
// 		rl_set_prompt(new_prompt);
// 		rl_redisplay();
// 	}
// }
