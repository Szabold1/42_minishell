/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:05:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/02 14:28:40 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execute the builtin command
static void	execute_builtin(t_data *data, int i)
{
	char	*cmd;

	cmd = data->cmds[i]->cmd_array[0];
	if (set_redirections(data, i) == ERROR)
		return ;
	if (ft_strcmp(cmd, "echo") == 0)
		ms_echo(data, i);
	else if (ft_strcmp(cmd, "cd") == 0)
		ms_cd(data, i);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ms_pwd(data, i);
	else if (ft_strcmp(cmd, "export") == 0)
		ms_export(data, i);
	else if (ft_strcmp(cmd, "unset") == 0)
		ms_unset(data, i);
	else if (ft_strcmp(cmd, "env") == 0)
		ms_env(data, i);
	else if (ft_strcmp(cmd, "exit") == 0)
		ms_exit(data, i);
	if (reset_stdin_out(data) == ERROR)
		err_msg("reset_stdin_out failed");
}

// handle the case when 'cmd_name' is not a valid, executable command, but it is a file
// print an error message and return the appropriate exit code
static int	handle_no_cmd_file(char *cmd_name)
{
	if (access(cmd_name, X_OK) != 0 && errno == EACCES
		&& ft_strchr(cmd_name, '/'))
		return (err_msg2(cmd_name, "Permission denied"), 126);
	else if (ft_strchr(cmd_name, '/'))
		return (err_msg2(cmd_name, "No such file or directory"), 127);
	else
		return (err_msg2(cmd_name, "command not found"), 127);
}

// handle the case when the command path is not found
// print an error message and exit with the appropriate exit code
static void	handle_no_path(t_data *data, int i)
{
	char	*cmd_name;
	int		exit_code;

	cmd_name = data->cmds[i]->cmd_array[0];
	if (is_directory(cmd_name) && ft_strchr(cmd_name, '/'))
	{
		err_msg2(cmd_name, "Is a directory");
		exit_code = 126;
	}
	else
		exit_code = handle_no_cmd_file(cmd_name);
	clean_up(data), close(1), exit(exit_code);
}

// child process, execute the command if possible, otherwise exit
static void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;
	int		exit_code;

	cmd = data->cmds[i];
	exit_code = 0;
	if (set_redirections(data, i) == ERROR)
		close_pipes(data), clean_up(data), exit(1);
	close_pipes(data);
	if (cmd->cmd_array[0][0] == '\0')
		clean_up(data), close(0), exit(0);
	if (cmd->cmd_path == NULL)
		handle_no_path(data, i);
	sig_cases(CHILD);
	close(data->fd_stdin);
	close(data->fd_stdout);
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	exit_code = handle_no_cmd_file(cmd->cmd_path);
	clean_up(data), exit(exit_code);
}

// execute a single command
int	execute_command(t_data *data, int i)
{
	pid_t	pid;

	if (data->cmds[i]->no_infile || data->cmds[i]->no_outfile)
		data->exit_status = 1;
	else if (is_builtin(data->cmds[i]->cmd_array[0]))
		execute_builtin(data, i);
	else
	{
		data->exit_status = 0;
		pid = fork();
		if (pid == -1)
			return (err_msg(strerror(errno)), ERROR);
		if (pid == 0)
			child_process(data, i);
		add_pid(data, pid);
	}
	return (OK);
}
