/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:48:11 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/10 10:16:27 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(ms()->exit_status) = 130;
}

void	handler_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	sanitize(true);
	(ms()->exit_status) = 130;
}

void	handler_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	(ms()->exit_status) = 128 + signum;
}
