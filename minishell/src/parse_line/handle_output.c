/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:57:39 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/08 11:03:43 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set output redirection
// 'mode' is 1 for '>', 2 for '>>'
// return ERROR or OK
static int	set_output(t_data *data, int i, int j, int mode)
{
	char	*file;

	file = data->command_split[i][j + 1];
	reset_fd(data->cmds[i]->fd_out);
	if (!file)
		return (err_msg("no output file after '>'"), ERROR);
	if (mode == 1)
		data->cmds[i]->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 2)
		data->cmds[i]->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->cmds[i]->fd_out == -1)
		return (err_msg2(file, strerror(errno)), ERROR);
	return (OK);
}

// handle output redirection ('>' or '>>')
// return ERROR or OK
int	handle_output(t_data *data, int i, int j)
{
	if (ft_strcmp(data->command_split[i][j], ">") == 0)
	{
		if (set_output(data, i, j, 1) == ERROR)
			return (ERROR);
	}
	else if (ft_strcmp(data->command_split[i][j], ">>") == 0)
	{
		if (set_output(data, i, j, 2) == ERROR)
			return (ERROR);
	}
	return (OK);
}
