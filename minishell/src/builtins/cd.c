/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:39:55 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 10:16:21 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change the current working directory,
// and update the environment variables 'OLDPWD' and 'PWD'
// handles 'cd' with no arguments, relative and absolute paths
void	ms_cd(t_data *data)
{
	char	**arr;
	char	*path;
	char	new_pwd[PATH_MAX];

	arr = ft_split(data->cmd_line, ' ');
	if (!arr)
		return ;
	path = arr[1];
	getcwd(new_pwd, PATH_MAX);
	if (!path)
	{
		if (ft_strlen(arr[0]) == 2 && chdir(ms_getenv("HOME", data)) == -1)
			perror("chdir");
	}
	else
	{
		if (chdir(path) == -1)
			perror("chdir");
	}
	ms_setenv("OLDPWD", ms_getenv("PWD", data), data);
	ms_setenv("PWD", new_pwd, data);
	ft_free_str_arr(arr);
}
