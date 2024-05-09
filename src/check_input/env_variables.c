/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:16:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/09 12:14:13 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the name of the environment variable starting at index 'i' in the 'str'
// return the name of the environment variable with $ prefix
// return value has to be freed
static char	*get_var_name(char *str, int i)
{
	int		j;
	char	*var_name;

	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
		j++;
	var_name = ft_substr(str, i, j - i);
	return (var_name);
}

// wrap the string in quotes
// 'str_p' is a pointer to the string that is wrapped in quotes
// 'quote' is the quote character that was found in the string
// return ERROR or OK
static int	wrap_in_quotes(char **str_p, char quote)
{
	char	*new_str;
	char	*outer_quote;

	if (quote == S_QUOTE)
		outer_quote = "\"";
	else
		outer_quote = "'";
	new_str = ft_strjoin(outer_quote, *str_p);
	if (!new_str)
		return (err_msg("ft_strjoin failed"), ERROR);
	free(*str_p);
	*str_p = ft_strjoin(new_str, outer_quote);
	if (!(*str_p))
		return (err_msg("ft_strjoin failed"), ERROR);
	free(new_str);
	return (OK);
}

// replace environment variable name with its value
// 'var_name' is the name of the environment variable (with $ prefix)
// 'str_p' is a pointer to the string where the replacement is done
// 'i' is the index of '$'
// return the value of the environment variable, or NULL if malloc fails
// example: ($USER -> user) ($nonexistent -> "")
static char	*replace_name_with_value(char *var_name, char **str_p,
	t_data *data, int i)
{
	char	*value;

	if (ft_strcmp(var_name, "$") == 0)
		value = ft_strdup("$");
	else
	{
		value = ms_getenv(var_name + 1, data);
		if (value)
			value = ft_strdup(value);
		if (ft_strchr(value, S_QUOTE))
			wrap_in_quotes(&value, S_QUOTE);
		else if (ft_strchr(value, D_QUOTE))
			wrap_in_quotes(&value, D_QUOTE);
		if (!value)
			value = ft_strdup("");
		if (!value)
			return (err_msg("ft_strdup failed"), NULL);
	}
	*str_p = ft_strreplace(*str_p, var_name, value, i);
	if (!(*str_p))
		return (err_msg("ft_strreplace failed"), NULL);
	return (value);
}

// this function is called when a '$' is found in the string,
// and replaces the environment variable or exit status with its value
// 'i' is the index of the '$'
// 'str_p' is a pointer to the string where the replacement is done
// return index of last character of the value in the string or ERROR
static int	replace_envvar(t_data *data, char **str_p, int i)
{
	char	*var_name;
	char	*value;

	if ((*str_p)[i] == '$' && (*str_p)[i + 1] == '?')
		return (replace_exit_status(data, str_p, i));
	var_name = get_var_name(*str_p, i);
	if (!var_name)
		return (ERROR);
	value = replace_name_with_value(var_name, str_p, data, i);
	if (value == NULL)
		return (free(var_name), ERROR);
	if (ft_strlen(value) == 0 && i == 0)
		i += 0;
	else
		i += ft_strlen(value) - 1;
	free(var_name);
	free(value);
	return (i);
}

// go through the string and replace all environment variables with their values
// 'str_p' is a pointer to the string where the replacement is done
// 'in_h' is true if the string is in a here document, false otherwise
// return ERROR or OK
int	replace_envvars_in_str(t_data *data, char **str_p, bool in_h)
{
	int		i;
	bool	in_dq;
	bool	in_sq;

	i = 0;
	in_dq = false;
	in_sq = false;
	while ((*str_p)[i])
	{
		if (ft_strncmp(*str_p + i, "<<", 2) == 0 && !in_sq && !in_dq && !in_h)
			skip_next_word(str_p, &i);
		if ((*str_p)[i] == D_QUOTE && !in_sq)
			in_dq = !in_dq;
		else if ((*str_p)[i] == S_QUOTE && !in_dq)
			in_sq = !in_sq;
		else if ((*str_p)[i] == '$' && (*str_p)[i + 1] && !in_sq)
		{
			i = replace_envvar(data, str_p, i);
			if (i == ERROR)
				return (ERROR);
		}
		if ((*str_p)[i])
			i++;
	}
	return (OK);
}
