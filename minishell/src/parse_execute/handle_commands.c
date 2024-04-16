/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 10:18:49 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// wait for all child processes to finish, and set the exit status if needed
static void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_count && data->cmds[i]->pid != -1)
	{
		waitpid(data->cmds[i]->pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
}

// execute a single command
static int	execute_command(t_data *data, int i)
{
	pid_t	pid;
	ft_printf_fd(2, "-------- execute_command --------\n"); // for testing
	ft_printf_fd(2, "%s fd_in: %d | fd_out: %d\n", data->cmds[i]->cmd_array[0], data->cmds[i]->fd_in, data->cmds[i]->fd_out); // for testing

	if (data->cmds[i]->no_infile || data->cmds[i]->no_outfile)
		data->exit_status = 1;
	else if (is_builtin(data->cmds[i]->cmd_array[0]))
		execute_builtin(data, i);
	else
	{
		pid = fork();
		if (pid == -1)
			return (err_msg(strerror(errno)), ERROR);
		if (pid == 0)
			child_process(data, i);
		data->cmds[i]->pid = pid;
	}
	return (OK);
}

// handle one command
// example: "grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
static int	handle_command(t_data *data, int i)
{
	if (set_cmd_in_out(data, i) == ERROR)
		return (err_msg("set_cmd_in_out failed"), ERROR);
	if (set_cmd_data(data, i) == ERROR)
		return (err_msg("set_cmd_data failed"), ERROR);

	// ft_printf_fd(2, "| cmd: %s\n", data->cmds[i]->cmd_array[0]); // for testing
	// ft_printf_fd(2, "| path: %s\n", data->cmds[i]->cmd_path); // for testing
	// ft_printf_fd(2, "| fd_in: %d\n", data->cmds[i]->fd_in); // for testing
	// ft_printf_fd(2, "|_fd_out: %d\n", data->cmds[i]->fd_out); // for testing

	if (execute_command(data, i) == ERROR)
		return (ERROR);
	return (OK);
}

// handle commands between pipes
// example: "ls -l | sort | grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
int	handle_commands(t_data *data)
{
	int	i;

	i = 0;
	while (data->line_split[i])
	{
		if (handle_command(data, i) == ERROR)
			return (ERROR);
		i++;
	}
	close_pipes(data);
	wait_for_processes(data);
	return (OK);
}
