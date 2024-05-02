/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:40:17 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/02 13:47:37 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set the command array to an empty string if there is no command
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

// create the command array, excluding the redirections
// example: echo hi < infile bye bye -> cmd_array = {"echo", "hi", "bye", "bye"}
static int	create_cmd_array(char **command_split, int start, char **cmd_array)
{
	int	i;

	i = 0;
	while (command_split[start])
	{
		if (command_split[start][0] == '\0')
			start++;
		else if (ft_strcmp(command_split[start], "<") == 0
			|| ft_strcmp(command_split[start], "<<") == 0
			|| ft_strcmp(command_split[start], ">") == 0
			|| ft_strcmp(command_split[start], ">>") == 0)
			start += 2;
		else
		{
			cmd_array[i] = ft_strdup(command_split[start]);
			if (!cmd_array[i])
				return (err_msg("ft_strdup failed"), ERROR);
			start++;
			i++;
		}
	}
	if (i == 0)
		cmd_array[i++] = ft_strdup("");
	cmd_array[i] = NULL;
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
	while (data->command_split[i][j])
		j++;
	len = j - start;
	cmd_array = malloc(sizeof(char *) * (len + 1));
	if (!cmd_array)
		return (err_msg("malloc failed"), NULL);
	if (create_cmd_array(data->command_split[i], start, cmd_array) == ERROR)
		return (NULL);
	return (cmd_array);
}

// find the path to the command in PATH
// return 'path' if successful, otherwise return NULL
static char	*find_path(t_data *data, char *cmd_name)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	cmd_name = remove_quotes(cmd_name);
	while (data->cmd_paths[i])
	{
		temp = ft_strjoin(data->cmd_paths[i], "/");
		if (!temp)
			return (err_msg("ft_strjoin failed"), NULL);
		path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (!path)
			return (err_msg("ft_strjoin failed"), NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

// find the path to the command
// return 'path' if successful, otherwise return NULL
static char	*get_cmd_path(t_data *data, int i)
{
	char	*cmd_name;
	int		len;

	cmd_name = data->cmds[i]->cmd_array[0];
	len = ft_strlen(cmd_name);
	if (access(cmd_name, F_OK) == 0 && !is_directory(cmd_name))
	{
		len = ft_strlen(cmd_name);
		if (ft_strcmp(cmd_name, "echo") == 0 || (ft_strchr(cmd_name, '/')
			&& len >= 4 && ft_strncmp(cmd_name + len - 4, "echo", 4) == 0))
		{
			free(data->cmds[i]->cmd_array[0]);
			data->cmds[i]->cmd_array[0] = ft_strdup("echo");
			if (!data->cmds[i]->cmd_array[0])
				return (err_msg("ft_strdup failed"), NULL);
			return (ft_strdup("echo"));
		}
		return (ft_strdup(cmd_name));
	}
	if (data->cmd_paths == NULL)
		return (NULL);
	return (find_path(data, cmd_name));
}

// set 'cmd_array' and 'cmd_path' in the command structure
// return ERROR if any of the steps fail, otherwise return OK
int	set_cmd_data(t_data *data, int i)
{
	int	start;

	start = 0;
	if (data->command_split[i][start] == NULL)
		return (set_cmd_empty(data, i));
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
