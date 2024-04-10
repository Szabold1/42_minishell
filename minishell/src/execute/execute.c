/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:15:04 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/10 16:16:35 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Execute a single command
static int execute_command(t_data *data, int i)
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

// Execute all commands in the line
int execute(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (ft_strcmp(data->cmds[i]->cmd_array[0], "exit") == 0)
			ms_exit(data);
		if (execute_command(data, i) == ERROR)
			return (ERROR);
		i++;
	}
	close_pipes(data);
	wait_for_processes(data);
	return (OK);
}
