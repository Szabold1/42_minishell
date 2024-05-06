/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_data_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:12:41 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/06 14:13:05 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*get_cmd_path(t_data *data, int i)
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
