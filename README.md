<h1 align="center">42_minishell</h1>

<p align="center">
  <a href="#about">About</a> &#xa0; | &#xa0;
  <a href="#features">Features</a> &#xa0; | &#xa0;
  <a href="#allowed-functions">Allowed functions</a> &#xa0; | &#xa0;
  <a href="https://github.com/Szabold1" target="_blank">Author</a>
</p>

<br>

<h3 align="center">🚧 Under construction...</h3>

## About

Minishell is a simple shell implementation written in C that provides basic shell functionalities. This shell aims to mimic some of the functionalities of a standard Unix shell like Bash.

## Features

- Displays a prompt when waiting for a new command.
- Maintains a working history of previously executed commands.
- Searches and launches the right executable based on the PATH variable or using a relative or absolute path.
- ...

## Allowed functions

The following functions were allowed to be used in this project:

| **Function**     | **Man**        | **Short Description**                                                    |
| ---------------- | -------------- | ------------------------------------------------------------------------ |
| readline         | man 3 readline | Reads a line from the terminal                                           |
| rl_clear_history |                | Clears the history list maintained by the GNU Readline library           |
| rl_on_new_line   |                |                                                                          |
| rl_replace_line  |                |                                                                          |
| rl_redisplay     |                |                                                                          |
| add_history      |                | Adds a line to the history list maintained by the GNU Readline library   |
| printf           | man 3 printf   | Prints formatted output to stdout                                        |
| malloc           | man 3 malloc   | Allocates a block of memory dynamically                                  |
| free             | man 3 free     | Deallocates a block of memory                                            |
| write            | man 2 write    | Writes data to a file descriptor                                         |
| access           | man 2 access   | Checks the accessibility of a file or directory                          |
| open             | man 2 open     | Opens a file or device and returns a file descriptor                     |
| read             | man 2 read     | Reads data from a file descriptor                                        |
| close            | man 2 close    | Closes a file descriptor                                                 |
| fork             | man 2 fork     | Creates a new process                                                    |
| wait             | man 2 wait     | Waits for a child process to terminate                                   |
| waitpid          | man 2 waitpid  | Waits for a specific child process to terminate                          |
| wait3            |                |                                                                          |
| wait4            |                |                                                                          |
| signal           |                |                                                                          |
| sigaction        |                |                                                                          |
| sigemptyset      |                |                                                                          |
| sigaddset        |                |                                                                          |
| kill             |                |                                                                          |
| exit             | man 3 exit     | Terminates the calling process                                           |
| getcwd           |                |                                                                          |
| chdir            |                |                                                                          |
| stat             |                |                                                                          |
| lstat            |                |                                                                          |
| fstat            |                |                                                                          |
| unlink           | man 2 unlink   | Deletes a name from the filesystem                                       |
| execve           | man 2 execve   | Executes a program                                                       |
| dup              | man 2 dup      | Duplicates a file descriptor                                             |
| dup2             | man 2 dup2     | Duplicates a file descriptor to a specified new descriptor               |
| pipe             | man 2 pipe     | Creates a pipe, a unidirectional communication channel                   |
| opendir          |                |                                                                          |
| readdir          |                |                                                                          |
| closedir         |                |                                                                          |
| strerror         | man 3 strerror | Returns a string describing the error code passed as argument            |
| perror           | man 3 perror   | Prints a descriptive error message to stderr based on the value of errno |
| isatty           |                |                                                                          |
| ttyname          |                |                                                                          |
| ttyslot          |                |                                                                          |
| ioctl            |                |                                                                          |
| getenv           |                |                                                                          |
| tcsetattr        |                |                                                                          |
| tcgetattr        |                |                                                                          |
| tgetent          |                |                                                                          |
| tgetflag         |                |                                                                          |
| tgetnum          |                |                                                                          |
| tgetstr          |                |                                                                          |
| tgoto            |                |                                                                          |
| tputs            |                |                                                                          |

Additionally, the following libraries were allowed:

- `libft`

<br>

<div align="center">
  Made by <a href="https://github.com/Szabold1" target="_blank">Boldizsar Szabo</a>
</div>
