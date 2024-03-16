#### MiniShell Project

🐚 This project is a simple shell implementation in C, designed to provide basic shell functionalities. It handles pipes, redirections, signals, command status, and includes seven built-in commands: `pwd`, `cd`, `echo`, `export`, `env`, `unset`, and `exit`. Additionally, it supports variable expansion and parsing of quotes and flags for commands.

#### Directory Structure

```
📁 builtins/
    - builtins.c
    - enviroment.c
    - expansor.c
    - history.c

📁 exec/
    - exec.c
    - finder.c
    - pipes.c

📁 parsing/
    - lexer.c
    - parsing.c
    - redirections.c

📁 utils/
    - frees.c
    - handler.c
    - inits.c

📄 main.c
📄 Makefile
```

#### Overview

**builtins/**: Contains implementations of built-in shell commands such as `cd`, `pwd`, `unset`, and `env`. Each file focuses on a specific builtin command.

**exec/**: Handles the execution of external commands. `exec.c` typically contains functions for executing commands in a new process.

**parsing/**: Responsible for parsing user input into commands and arguments. `parsing.c` contains functions like `parse_command`, which parses input commands and adds them to history.

**utils/**: Contains utility functions and handlers for various tasks. `handler.c` includes the `handle_builtin_commands` function for executing builtin commands, and `frees.c` manages memory deallocation.

**main.c**: The entry point of the program. It sets up command history, handles signals, and executes user commands.

#### Build and Run

To build the project, use the provided Makefile or a similar build system. Once built, run the shell by executing the resulting binary (`./minishell`). Note that this is a simplified shell and may not support all features of full-fledged shells like bash or zsh.

```bash
make
./minishell
```
