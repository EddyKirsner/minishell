/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:35:51 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 17:05:56 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler1(int signal)
{
	(void)signal;
	g_sig = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler2(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_sig = 1;
}

void	sigquit_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "Quit\n", 5);
	g_sig = 1;
}

void	interactive_sig1(void)
{
	struct sigaction	sig_ctrlc;
	struct sigaction	sig_ctrlslash;

	bzero(&sig_ctrlc, sizeof(sig_ctrlc));
	sig_ctrlc.sa_handler = &sigint_handler1;
	sig_ctrlc.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_ctrlc, NULL);
	bzero(&sig_ctrlslash, sizeof(sig_ctrlslash));
	sig_ctrlslash.sa_handler = SIG_IGN;
	sig_ctrlslash.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_ctrlslash, NULL);
}

void	interactive_sig2(void)
{
	struct sigaction	sig_ctrlc;
	struct sigaction	sig_ctrlslash;

	bzero(&sig_ctrlc, sizeof(sig_ctrlc));
	sig_ctrlc.sa_handler = &sigint_handler2;
	sig_ctrlc.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_ctrlc, NULL);
	bzero(&sig_ctrlslash, sizeof(sig_ctrlslash));
	sig_ctrlslash.sa_handler = &sigquit_handler;
	sig_ctrlslash.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_ctrlslash, NULL);
}
