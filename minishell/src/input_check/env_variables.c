/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:16:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/24 14:07:07 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the name of the environment variable starting at index 'i'
// return the name of the environment variable with $ prefix
// return value has to be freed
static char	*get_var_name(char *line, int i)
{
	int		j;
	char	*var_name;

	j = i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	var_name = ft_substr(line, i, j - i);
	return (var_name);
}

// replace environment variables with their values in double quotes
// return index of next double quote or index of null terminator
// example: echo "Hello $USER $PWD" -> echo "Hello user /home/user"
int	replace_env_variables_in_quotes(t_data *data, int q_start, int q_end)
{
	int		i;
	char	*var_name;
	char	*value;

	i = q_start;
	while (i < q_end)
	{
		if (data->line[i] == '$' && data->line[i + 1])
		{
			var_name = get_var_name(data->line, i);
			value = ms_getenv(var_name + 1, data);
			if (!value)
				value = "";
			data->line = ft_strreplace(data->line, var_name, value);
			if (!data->line)
				return (err_msg("ft_strreplace failed"), ERROR);
			i += ft_strlen(value) - 1;
			q_end += ft_strlen(value) - ft_strlen(var_name);
			free(var_name);
		}
		i++;
	}
	return (q_end);
}

// replace environment variable name with its value if not in quotes
// return index of last character of the value or ERROR
int	replace_env_variable(t_data *data, int i)
{
	char	*var_name;
	char	*value;

	var_name = get_var_name(data->line, i);
	value = ms_getenv(var_name + 1, data);
	if (!value)
		value = "";
	data->line = ft_strreplace(data->line, var_name, value);
	free(var_name);
	if (!data->line)
		return (err_msg("ft_strreplace failed"), ERROR);
	if (ft_strlen(value) == 0 && i == 0)
		i += ft_strlen(value);
	else
		i += ft_strlen(value) - 1;
	return (i);
}
