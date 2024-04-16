/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:53:52 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 19:21:24 by bszabo           ###   ########.fr       */
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

// set the value of the environment variable 'name' to 'value'
void	ms_setenv(char *name, char *value, t_data *data)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0)
		{
			if (data->env[i][len] == '=')
			{
				free(data->env[i]);
				temp = ft_strjoin("=", value);
				if (temp == NULL)
					return (err_msg("ft_strjoin failed"));
				data->env[i] = ft_strjoin(name, temp);
				free(temp);
				if (data->env[i] == NULL)
					err_msg("ft_strjoin failed");
				return ;
			}
		}
		i++;
	}
}

// print the environment
void	ms_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	data->exit_status = 0;
}
