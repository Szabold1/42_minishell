/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:39:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/06 09:34:41 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialize data structure and its members
// return OK if successful, ERROR if not
int	init(t_data *data, char *env[])
{
	data->env = ft_strdup_arr(env);
	if (!data->env)
		return (ERROR);
	data->line = NULL;
	data->line_split = NULL;
	data->command_split = NULL;
	data->cmd_paths = ft_split(getenv("PATH"), ':');
	if (!data->cmd_paths)
		return (ERROR);
	data->cmds = NULL;
	data->pipes = NULL;
	data->pids_child = NULL;
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->no_infile = false;
	data->exit_status = 0;
	return (OK);
}