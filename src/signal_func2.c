/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:03:36 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 17:22:41 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	interactive_sig_heredoc(void)
{
	struct sigaction	sig_ctrlc;
	struct sigaction	sig_ctrlslash;

	bzero(&sig_ctrlc, sizeof(sig_ctrlc));
	sig_ctrlc.sa_handler = &sigint_handler2;
	sigaction(SIGINT, &sig_ctrlc, NULL);
	bzero(&sig_ctrlslash, sizeof(sig_ctrlslash));
	sig_ctrlslash.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_ctrlslash, NULL);
}
