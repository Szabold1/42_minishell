/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:16:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/19 18:17:59 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// replace environment variable name with its value
// it will update the line, example: echo $USER -> echo username
// return OK or ERROR 
static int	replace_env_variable(t_data *data, int *i)
{
	int		j;
	char	*var_name;
	char	*value;

	j = *i + 1;
	while (data->line[j] && (ft_isalnum(data->line[j]) || data->line[j] == '_'))
		j++;
	var_name = ft_substr(data->line, *i + 1, j - *i - 1);
	value = ms_getenv(var_name, data);
	if (!value)
		value = "";
	data->line = ft_strreplace(data->line, *i, value);
	if (!data->line)
		return (ERROR);
	*i += ft_strlen(value);
	return (OK);
}

// replace environment variables with their values if not in single quotes
// return OK or ERROR
int	handle_env_variables(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == S_QUOTE)
			i = find_next_quote(data->line, i, S_QUOTE);
		else if (data->line[i] == '$' && data->line[i + 1])
		{
			if (replace_env_variable(data, &i) == ERROR)
				return (ERROR);	
		}
		i++;
	}
	return (OK);
}
