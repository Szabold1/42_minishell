/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:08:25 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 13:45:36 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a copy of the environment variables so that we can modify them
char	**init_envp(char *envp[])
{
	int		i;
	char	**my_envp;

	i = 0;
	while (envp[i])
		i++;
	my_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!my_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
			return (NULL);
		i++;
	}
	my_envp[i] = NULL;
	return (my_envp);
}

// initialize all the data
int	init(t_data *data, char *envp[])
{
	data->exit_status = 0;
	data->cmd_line = NULL;
	data->my_envp = init_envp(envp);
	if (!data->my_envp)
		return (ft_printf_fd(2, "Error: init 'my_envp'\n"), -1);
	data->paths_arr = ft_split(getenv("PATH"), ':');
	if (!data->paths_arr)
		return (ft_printf_fd(2, "Error: init 'paths_arr'\n"), -1);
	return (0);
}