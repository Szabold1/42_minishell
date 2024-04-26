/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:54 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/25 17:55:47 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// surround first 'substr' with spaces in 'str' starting at index 'start_i'
// 'str' is a pointer to the string where the replacement is done
// return ERROR or OK
// example: ("hello>>file", ">>", 5) -> "hello >> file"
int	surround_with_spaces(char **str, char *substr, int start_i)
{
	char	*temp;
	char	*new_substr;

	if (!ft_strnstr(*str + start_i, substr, 2))
		return (ERROR);
	temp = ft_strjoin(" ", substr);
	if (!temp)
		return (ERROR);
	new_substr = ft_strjoin(temp, " ");
	free(temp);
	if (!new_substr)
		return (ERROR);
	*str = ft_strreplace(*str, substr, new_substr, start_i);
	free(new_substr);
	if (!*str)
		return (ERROR);
	return (OK);
}

// part of separate_redirections, handle input redirections (<, <<)
// return ERROR or the index of space after the redirections
static int	separate_redirections_in(t_data *data, int i)
{
	if (data->line[i + 1] == '<')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		if (surround_with_spaces(&(data->line), "<<", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with_spaces(&(data->line), "<", i) == ERROR)
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
		if (surround_with_spaces(&(data->line), ">>", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with_spaces(&(data->line), ">", i) == ERROR)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// separate redirections in the line starting at index 'i'
// example: (i = 2) ls>file -> ls > file (return 4)
// return ERROR or the index of space after the redirection symbol
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
