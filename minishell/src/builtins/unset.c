/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:40 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/17 10:06:50 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the index of the environment variable in the data structure env
// return ERROR if the variable is not found
static int	get_envvar_index(t_data *data, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == 0)
		{
			if (data->env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (ERROR);
}

// remove the environment variable from the data structure env
// by freeing the memory and shifting the elements
static void	remove_envvar(t_data *data, char *var_name)
{
	int	i;
	int	index;

	index = get_envvar_index(data, var_name);
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
	char	**cmd_array;
	int		j;

	cmd_array = data->cmds[i]->cmd_array;
	j = 1;
	if (i == 0 && data->cmd_count == 1)
	{
		while (cmd_array[j])
			remove_envvar(data, cmd_array[j++]);
	}
	data->exit_status = 0;
}
