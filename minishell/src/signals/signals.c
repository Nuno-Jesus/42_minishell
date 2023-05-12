/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:45:25 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/10 09:43:08 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
}

void	signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
