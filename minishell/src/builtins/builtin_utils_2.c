/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:41 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/21 12:32:21 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// remove necessary quotes from string, return the modified string
// example: test_"hello'world" -> test_hello'world
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	bool	in_s_quote;
	bool	in_d_quote;

	i = 0;
	j = 0;
	in_s_quote = false;
	in_d_quote = false;
	while (str[i])
	{
		if (str[i] == S_QUOTE && !in_d_quote)
			in_s_quote = !in_s_quote;
		else if (str[i] == D_QUOTE && !in_s_quote)
			in_d_quote = !in_d_quote;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

// get the index of the environment variable in the data structure env
// return ERROR if the variable is not found
int	ms_getenv_index(t_data *data, char *var_name)
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

// get the name of the environment variable 'env_var'
// example: VAR_NAME=VAR_VALUE will return VAR_NAME
char	*get_env_name(char *env_var)
{
	int		i;
	char	*name;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	name = ft_substr(env_var, 0, i);
	if (name == NULL)
		err_msg("ft_substr failed");
	return (name);
}
