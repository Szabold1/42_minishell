/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:39:55 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 14:20:09 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_errors(char **arr, t_data *data)
{
	if (ft_strlen(arr[0]) != 2)
	{
		err_msg(arr[0], "command not found");
		ft_free_str_arr(arr);
		data->exit_status = 127;
		return (-1);
	}
	if (arr[1] && arr[2])
	{
		err_msg("cd", "too many arguments");
		ft_free_str_arr(arr);
		data->exit_status = 1;
		return (-1);
	}
	return (0);
}

// change the current working directory,
// and update the environment variables 'OLDPWD' and 'PWD'
// handles 'cd' with no arguments, relative and absolute paths
void	ms_cd(t_data *data)
{
	char	**arr;
	char	new_pwd[PATH_MAX];

	arr = ft_split(data->cmd_line, ' ');
	if (!arr)
		return ;
	if (check_errors(arr, data) == -1)
		return ;
	if (!arr[1])
	{
		if (chdir(ms_getenv("HOME", data)) == -1)
			return (err_msg("cd", strerror(errno)), ft_free_str_arr(arr));
	}
	else
	{
		if (chdir(arr[1]) == -1)
		{
			data->exit_status = 1;
			return (err_msg(arr[1], strerror(errno)), ft_free_str_arr(arr));
		}
	}
	ms_setenv("OLDPWD", ms_getenv("PWD", data), data);
	getcwd(new_pwd, PATH_MAX);
	ms_setenv("PWD", new_pwd, data);
	ft_free_str_arr(arr);
}
