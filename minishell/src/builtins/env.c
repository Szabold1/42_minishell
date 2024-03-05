/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:45:50 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 09:48:41 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// update the environment variable 'var_name'
// return 0 if successful, -1 if not
static int	update_env_var(char *var_name, char *value, char *envp[], int i)
{
	char	*temp;
	char	*new_var;

	temp = ft_strjoin(var_name, "=");
	if (!temp)
		return (-1);
	new_var = ft_strjoin(temp, value);
	if (!new_var)
		return (free(temp), -1);
	free(temp);
	free(envp[i]);
	envp[i] = new_var;
	return (0);
}

// set the environment variable 'var_name''s value to 'value'
// return 0 if successful, -1 if not
int	ms_setenv(char *var_name, char *value, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->my_envp[i])
	{
		if (ft_strncmp(data->my_envp[i], var_name, len) == 0)
			return (update_env_var(var_name, value, data->my_envp, i));
		i++;
	}
	return (-1);
}

// get the environment variable 'var_name''s value
// return the value if successful, NULL if not
char	*ms_getenv(char *var_name, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->my_envp[i])
	{
		if (ft_strncmp(data->my_envp[i], var_name, len) == 0)
			return (data->my_envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// print the environment variables
void	ms_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}