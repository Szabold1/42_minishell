/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/01 19:20:53 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle one command
// example: "grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
int	handle_command(t_data *data, int i)
{
	if (set_cmds_array(data, i) == ERROR)
		return (ERROR);
	// if (execute(data, i) == ERROR)
	// 	return (ERROR);
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
