/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:55:39 by seckhard          #+#    #+#             */
/*   Updated: 2024/04/10 20:02:55 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_quit(int signal)
{
	t_data	*data;

	(void)signal;
	data = NULL;
	ft_printf("Quit (core dumped)\n");
	data->exit_status = 131;
	kill(0, SIGCHLD);
}

void	heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = CTRLC;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

// Sets signals for different modes
void	sig_cases(t_data *data, int sig_status)
{
	if (!data)
		return ;
	if (sig_status == INTERACTIVE)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_status == NONINTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, &sig_quit);
	}
	else if (sig_status == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_status == HEREDOC)
	{
		signal(SIGINT, &heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
