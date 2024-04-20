/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:40 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/17 17:43:26 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// remove the environment variable from the data structure env
// by freeing the memory and shifting the elements
static void	remove_envvar(t_data *data, char *var_name)
{
	int	i;
	int	index;

	var_name = remove_quotes(var_name);
	index = ms_getenv_index(data, var_name);
	if (index == ERROR)
		return ;
	free(data->env[index]);
	i = index;
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}

// remove the environment variable from the data structure env
void	ms_unset(t_data *data, int i)
{
	char	**unset_arg;
	int		j;

	unset_arg = data->cmds[i]->cmd_array;
	j = 1;
	if (i == 0 && data->cmd_count == 1)
	{
		while (unset_arg[j])
			remove_envvar(data, unset_arg[j++]);
	}
	data->exit_status = 0;
}
