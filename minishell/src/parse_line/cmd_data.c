/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:40:17 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/12 08:45:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_cmd_empty(t_data *data, int i)
{
	data->cmds[i]->cmd_array = malloc(sizeof(char *) * 2);
	if (!data->cmds[i]->cmd_array)
		return (err_msg("malloc failed"), ERROR);
	data->cmds[i]->cmd_array[0] = ft_strdup("");
	if (!data->cmds[i]->cmd_array[0])
		return (err_msg("ft_strdup failed"), ERROR);
	data->cmds[i]->cmd_array[1] = NULL;
	return (OK);
}

// extract the command array from the command split
// return 'cmd_array' if successful, otherwise return NULL
static char	**get_cmd_array(t_data *data, int i, int start)
{
	int		j;
	int		len;
	char	**cmd_array;

	j = start;
	len = 0;
	while (data->command_split[i][j] && data->command_split[i][j][0] != '<'
		&& data->command_split[i][j][0] != '>')
		j++;
	len = j - start;
	cmd_array = malloc(sizeof(char *) * (len + 1));
	if (!cmd_array)
		return (err_msg("malloc failed"), NULL);
	j = 0;
	while (j < len && data->command_split[i][start + j][0] != '<'
		&& data->command_split[i][start + j][0] != '>')
	{
		cmd_array[j] = ft_strdup(data->command_split[i][start + j]);
		if (!cmd_array[j])
			return (err_msg("ft_strdup failed"), NULL);
		j++;
	}
	cmd_array[j] = NULL;
	return (cmd_array);
}

// find the path to the command
// return 'path' if successful, otherwise return NULL
static char	*get_cmd_path(t_data *data, int i)
{
	int		j;
	char	*temp;
	char	*path;

	j = 0;
	if (access(data->cmds[i]->cmd_array[0], F_OK) == 0)
		return (ft_strdup(data->cmds[i]->cmd_array[0]));
	while (data->cmd_paths[j])
	{
		temp = ft_strjoin(data->cmd_paths[j], "/");
		if (!temp)
			return (err_msg("ft_strjoin failed"), NULL);
		path = ft_strjoin(temp, data->cmds[i]->cmd_array[0]);
		free(temp);
		if (!path)
			return (err_msg("ft_strjoin failed"), NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		j++;
	}
	return (NULL);
}

// set 'cmd_array' and 'cmd_path' in the command structure
// return ERROR if any of the steps fail, otherwise return OK
int	set_cmd_data(t_data *data, int i)
{
	int	start;

	start = 0;
	while (data->command_split[i][start][0] == '<'
		|| data->command_split[i][start][0] == '>')
	{
		start += 2;
		if (data->command_split[i][start] == NULL)
			return (set_cmd_empty(data, i));
	}
	data->cmds[i]->cmd_array = get_cmd_array(data, i, start);
	if (!data->cmds[i]->cmd_array)
		return (ERROR);
	data->cmds[i]->cmd_path = get_cmd_path(data, i);
	return (OK);
}
