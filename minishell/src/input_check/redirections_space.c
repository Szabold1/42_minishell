/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:54 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/27 15:35:12 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// surround first 'substr' with spaces in 'str' starting at index 'start_i'
// return new string with spaces added, or NULL if malloc fails
// example: ("hello>>file", ">>", 5) -> "hello >> file"
static char	*surround_with_spaces(t_data *data, char *substr, int start_i)
{
	char	*temp;
	char	*new_substr;

	if (!ft_strnstr(data->line + start_i, substr, 2))
		return (NULL);
	temp = ft_strjoin(" ", substr);
	if (!temp)
		return (NULL);
	new_substr = ft_strjoin(temp, " ");
	free(temp);
	if (!new_substr)
		return (NULL);
	data->line = ft_strreplace(data->line, substr, new_substr, start_i);
	free(new_substr);
	if (!data->line)
		return (NULL);
	return (data->line);
}

// part of separate_redirections, handle input redirections (<, <<)
// return ERROR or the index of space after the redirections
static int	separate_redirections_in(t_data *data, int i)
{
	if (data->line[i + 1] == '<')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		data->line = surround_with_spaces(data, "<<", i);
		if (data->line == NULL)
			return (ERROR);
		i += 3;
	}
	else
	{
		data->line = surround_with_spaces(data, "<", i);
		if (data->line == NULL)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// part of separate_redirections, handle output redirections (>, >>)
// return ERROR or the index of space after the redirections
static int	separate_redirections_out(t_data *data, int i)
{
	if (data->line[i + 1] == '>')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		data->line = surround_with_spaces(data, ">>", i);
		if (data->line == NULL)
			return (ERROR);
		i += 3;
	}
	else
	{
		data->line = surround_with_spaces(data, ">", i);
		if (data->line == NULL)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// separate redirections in the line
// example: ls>file -> ls > file
// return ERROR or the index of space after the redirections
int	separate_redirections(t_data *data, int i)
{
	if (data->line[i] == '<')
	{
		i = separate_redirections_in(data, i);
		if (i == ERROR)
			return (ERROR);
	}
	else
	{
		i = separate_redirections_out(data, i);
		if (i == ERROR)
			return (ERROR);
	}
	return (i);
}
