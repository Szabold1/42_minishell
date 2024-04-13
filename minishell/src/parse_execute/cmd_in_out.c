/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:03:50 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/13 10:00:50 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check redirections ('<', '<<', '>', '>>') and set fd_in, fd_out accordingly
// return ERROR or OK
int	set_cmd_in_out(t_data *data, int i)
{
	int	j;

	j = 0;
	if (i > 0 && data->cmds[i - 1]->no_infile)
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
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
