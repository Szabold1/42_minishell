/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:39:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/19 21:14:34 by bszabo           ###   ########.fr       */
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
	data->cmd_paths = ft_split(getenv("PATH"), ':');
	if (!data->cmd_paths)
		return (ERROR);
	data->cmds = NULL;
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->exit_status = 0;
	return (OK);
}