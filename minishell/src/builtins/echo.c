/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:27 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/11 19:25:56 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if the argument has quotes around it, remove them, and return it without
// the quotes, if it doesn't have any return a copy of the argument
static char	*get_cur_arg(char *arg)
{
	if (arg[0] == S_QUOTE)
		return (ft_strtrim(arg, "\'"));
	else if (arg[0] == D_QUOTE)
		return (ft_strtrim(arg, "\""));
	else
		return (ft_strdup(arg));
}

// print the argument
static void	print_arg(char **cmd_array, int j, bool *newline)
{
	char	*cur_arg;
	
	cur_arg = get_cur_arg(cmd_array[j]);
	if (!cur_arg)
		return ;
	if(j == 1 && ft_strcmp(cmd_array[j], "-n") == 0)
		*newline = false;
	else
	{
		printf("%s", cur_arg);
		if (cmd_array[j + 1])
			printf(" ");	
	}
	free(cur_arg);
}

// print the arguments of the echo command, handle the -n flag
void	ms_echo(t_data *data, int i)
{
	int		j;
	bool	newline;
	char	**cmd_array;

	j = 1;
	newline = true;
	cmd_array = data->cmds[i]->cmd_array;
	while (cmd_array[j])
	{
		print_arg(cmd_array, j, &newline);
		j++;
	}
	if (newline)
		printf("\n");
	data->exit_status = 0;
}
