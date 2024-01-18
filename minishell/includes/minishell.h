/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/01/18 08:56:36 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"

/*-----------------------------------------INCLUDES--------------------------------*/
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
/*---------------------------------------------------------------------------------*/
/*-----------------------------------------DEFINES--------------------------------*/
# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define DELIMITERS " \t\r\n\a"
/*---------------------------------------------------------------------------------*/

/*-----------------------------------------STRUCTURES-----------------------------*/
typedef struct CommandHistory
{
	char *commands[MAX_HISTORY];
	int index;
} CommandHistory;

typedef struct {
	char *name;
	void (*func)(char **);
} Commandenv;

typedef struct {
	char *name;
	void (*func)(char **);
} Command;

/*---------------------------------------------------------------------------------*/
extern char			**environ;
extern				Command commands[];
extern				Commandenv commandsenv[];
/*---------------BUILTINS----------------------------------------------------------*/
void				cmd_pwd();
char*				cmd_history(CommandHistory* history);
void				cmd_unset(char **args);
void				cmd_env(char **environ);
void				cmd_export(char **args);
void				cmd_echo(char **args);
void				cmd_cd(char **args);
void				print_header(void);
void				handle_sigint(int sig);
/*---------------HISTORY-----------------------------------------------------------*/
void				add_to_history(CommandHistory* history, char *command);
char				*get_from_history(CommandHistory* history, int index);
void				destroy_history(CommandHistory* history);
CommandHistory*		create_history(void);
/*---------------EXEC--------------------------------------------------------------*/
char				*find_command(char *command);
void				execute_builtin_command(char **args);
int					execute_external_command(char **args);
void				 execute_pipe(int fd[2], char **args);
void				execute_builtin_commandenv(char **args, char **environ);
/*---------------PARSER------------------------------------------------------------*/
void				parse_command(char *input, CommandHistory* history);
void				chose_command(char *commands[], int n);
void				chose_pipe(char *commands[], int n);
/*---------------TOKENIZATION---------------------------------------------------*/
char				**token_pipe_cmd(char *command[], int n);
char				**token_single_cmd(char *command[], int n);

#endif
