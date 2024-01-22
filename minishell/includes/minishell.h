/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/01/22 03:02:22 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

/*-----------------------------------------INCLUDES------------------*/
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
/*------------------------------------------------------------------------*/
/*-----------------------------------------DEFINES-----------------------*/
# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define DELIMITERS " \t\r\n\a"
/*---------------------------------------------------------------*/

/*-----------------------------------------STRUCTURES---------------*/
typedef struct CommandHistory
{
	char	*commands[MAX_HISTORY];
	int		index;
}t_commandhistory;

/*-------------------------------------------------------------*/
extern char			**environ;
/*---------------BUILTINS-------------------------------------------*/
int					cmd_pwd(void);
char				*cmd_history(t_commandhistory *history);
int					cmd_unset(char **args);
void				cmd_env(char **environ);
int					cmd_export(char **args);
int					cmd_echo(char **args);
int					cmd_cd(char **args);
/*---------------HISTORY-------------------------------------*/
void				add_to_history(t_commandhistory *history, char *command);
char				*get_from_history(t_commandhistory *history, int index);
void				destroy_history(t_commandhistory *history);
t_commandhistory	*create_history(void);
/*---------------EXEC-----------------------------------------*/
char				*find_command(char *command);
void				execute_builtin_command(char **args, int *exit_status);
int					execute_external_command(char **args);
void				execute_pipe(int fd[2], char **args);
void				execute_builtin_commandenv(char **args, char **environ);
/*---------------PARSER--------------------------------------------*/
void				parse_command(char *input, t_commandhistory *history);
void				chose_command(char *commands[], int n);
void				chose_pipe(char *commands[], int n);
/*---------------TOKENIZATION---------------------------------*/
char				**token_pipe_cmd(char *command[], int n);
/*---------------REDIRECTION---------------------------------*/
void				handle_here_document(char *delimiter);
char				**handle_redirection(char **args, int *orig_stdin, \
					int *orig_stdout);
void				chose_redirection(char **args, int i);
/*---------------UTILS-----------------------------------------*/
int					is_single_quote(char *str, int index);
void				restore_io(int orig_stdin, int orig_stdout);
void				handle_sigint(int sig);
void				print_header(void);
void				free_malloced(char *commands[], int is_malloced[], int i);
int					chose_built_in(char **args, int *exit_status);

#endif
