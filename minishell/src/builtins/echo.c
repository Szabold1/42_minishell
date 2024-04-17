/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:27 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/17 17:33:54 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the argument
static void	print_arg(char **echo_arg, int j, bool *newline)
{
	echo_arg[j] = remove_quotes(echo_arg[j]);
	if(j == 1 && ft_strcmp(echo_arg[j], "-n") == 0)
		*newline = false;
	else
	{
		printf("%s", echo_arg[j]);
		if (echo_arg[j + 1])
			printf(" ");
	}
}

// print the arguments of the echo command, handle the -n flag
void	ms_echo(t_data *data, int i)
{
	int		j;
	bool	newline;
	char	**echo_arg;

	j = 1;
	newline = true;
	echo_arg = data->cmds[i]->cmd_array;
	while (echo_arg[j])
		print_arg(echo_arg, j++, &newline);
	if (newline)
		printf("\n");
	data->exit_status = 0;
}
