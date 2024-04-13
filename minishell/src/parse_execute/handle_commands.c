/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/13 10:14:00 by bszabo           ###   ########.fr       */
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

	pid = fork();
	if (pid == -1)
		return (err_msg(strerror(errno)), ERROR);
	if (pid == 0)
		child_process(data, i);
	data->cmds[i]->pid = pid;
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

	printf("| cmd: %s\n", data->cmds[i]->cmd_array[0]); // for testing
	printf("| path: %s\n", data->cmds[i]->cmd_path); // for testing
	printf("| fd_in: %d\n", data->cmds[i]->fd_in); // for testing
	printf("| fd_out: %d\n", data->cmds[i]->fd_out); // for testing
	printf("|_pid: %d\n", data->cmds[i]->pid); // for testing

	if (ft_strcmp(data->cmds[i]->cmd_array[0], "exit") == 0)
		ms_exit(data);
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
