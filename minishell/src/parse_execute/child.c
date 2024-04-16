/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:05:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 10:10:05 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// child process, execute the command if possible, otherwise exit
void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmds[i];
	if (set_redirections(data, i) == ERROR)
		close_pipes(data), clean_up(data), exit(1);
	close_pipes(data);
	if (cmd->no_infile || cmd->no_outfile)
		clean_up(data), exit(1);
	if (cmd->cmd_array[0][0] == '\0')
		clean_up(data), exit(0);
	if (cmd->cmd_path == NULL)
	{
		err_msg2(cmd->cmd_array[0], "command not found");
		clean_up(data), exit(127);
	}
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	err_msg(strerror(errno)), clean_up(data), exit(1);
}
