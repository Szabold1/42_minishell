/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/08 10:47:21 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check redirections ('<', '<<', '>', '>>') and set fd_in, fd_out accordingly
// return ERROR or OK
static int	set_cmd_in_out(t_data *data, int i)
{
	int	j;

	j = 0;
	if (i > 0 && data->cmds[i - 1]->no_infile)
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
		ft_printf_fd(2, "no infile fd: %d\n", data->cmds[i]->fd_in);
	}
	while (data->command_split[i][j])
	{
		if (handle_input(data, i, j) == ERROR)
			return (ERROR);
		if (handle_output(data, i, j) == ERROR)
			return (ERROR);
		j++;
	}
	return (OK);
}

// handle one command
// example: "grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
static int	handle_command(t_data *data, int i)
{
	if (set_cmd_in_out(data, i) == ERROR)
		return (ERROR);
	if (set_cmd_data(data, i) == ERROR)
		return (ERROR);
	printf("| cmd: %s\n", data->cmds[i]->cmd_array[0]); // for testing
	printf("| path: %s\n", data->cmds[i]->cmd_path); // for testing
	printf("| fd_in: %d\n", data->cmds[i]->fd_in); // for testing
	printf("| fd_out: %d\n", data->cmds[i]->fd_out); // for testing
	printf("|_pid: %d\n", data->cmds[i]->pid); // for testing
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
	return (OK);
}
