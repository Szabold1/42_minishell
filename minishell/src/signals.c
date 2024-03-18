/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:55:39 by seckhard          #+#    #+#             */
/*   Updated: 2024/03/18 22:32:29 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// to do: heredoc


void sig_cases(t_data *data, int sig_status)
{
	if (!data)
		return;
	if (sig_status == INTERACTIVE)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	// else if (sig_status == NONINTERACTIVE)
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// }
}
