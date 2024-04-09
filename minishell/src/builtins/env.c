/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:53:52 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/08 12:35:15 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the value of the environment variable 'name'
// return pointer to the value if it exists, NULL otherwise
char	*ms_getenv(char *name, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0)
		{
			if (data->env[i][len] == '=')
				return (data->env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

void	ms_env(t_data *data)
{
	ft_printf_fd(2, "ms_env()\n");
	ft_printf_fd(2, "%s\n", data->line);
}
