# MiniShell Project

🐚 This project is a simple shell implementation in C, designed to provide basic shell functionalities. It is organized into several directories, each containing related source files:

## Directory Structure

```
📁 builtins/
    - history.c
    - cd.c
    - pwd.c
    - unset.c
    - env.c

📁 exec/
    - exec.c

📁 parsing/
    - parsing.c

📁 utils/
    - handler.c

📄 main.c
```

## Overview

### builtins/

This directory contains the implementation of builtin shell commands like `cd`, `pwd`, `unset`, and `env`. Each file in this directory focuses on a specific builtin command. For instance:

- `history.c` manages command history functions such as `add_to_history`, `get_from_history`, and `destroy_history`.
- `cd.c` handles changing directories.
- `pwd.c` manages printing the current working directory.
- `unset.c` handles unsetting environment variables.
- `env.c` manages displaying environment variables.

### exec/

🚀 The `exec/` directory handles the execution of external commands. The `exec.c` file typically contains functions for executing commands in a new process.

### parsing/

🔍 This directory is responsible for parsing user input into commands and arguments. The `parsing.c` file contains functions like `parse_command`, which parses input commands and adds them to history, and `handle_commands`, which executes commands.

### utils/

🛠️ Contains utility functions and handlers for various tasks. The `handler.c` file includes the `handle_builtin_commands` function, which executes builtin commands.

### main.c

🚀 The entry point of the program. It sets up command history, handles signals, and enters a loop to read and execute user commands. It also contains the `handle_sigint` function, which handles the SIGINT signal (Ctrl+C) to stop the currently running process.

## Build and Run

To build the project, typically use a Makefile or a similar build system. Once built, run the shell by executing the resulting binary. Note that this is a simplified shell and may not support all features of full-fledged shells like bash or zsh.

```bash
make
./minishell
```
