/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/01/04 23:54:30 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

extern char	**environ;

# define MAX_INPUT_SIZE 1024
#define MAX_HISTORY 100
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n\a"

typedef struct CommandHistory
{
	char *commands[MAX_HISTORY];
	int index;
} CommandHistory;

/*---------------UTILS------------------------------------------------------------*/
char			**split_string(char *str, char *delimiters);
/*---------------BUILTINS----------------------------------------------------------*/
void			cmd_echo(char **args, CommandHistory* history);
void			cmd_pwd(char **args, CommandHistory* history);
void			cmd_unset(char **args, CommandHistory* history);
void			cmd_cd(char **args, CommandHistory* history);
void			cmd_env(char **args, char **environ, CommandHistory* history);
void			cmd_export(char **args, CommandHistory* history);
char*			cmd_history(CommandHistory* history);
void			execute_command(char **args, char **environ, CommandHistory* history);
/*---------------HISTORY-----------------------------------------------------------*/
void			add_to_history(CommandHistory* history, char *command);
char			*get_from_history(CommandHistory* history, int index);
CommandHistory*	create_history(void);

#endif
