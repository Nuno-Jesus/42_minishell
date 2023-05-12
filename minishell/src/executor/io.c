/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:56:15 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 12:56:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_connect(void)
{
	if (ms()->in_fd >= STDIN_FILENO)
		dup2(ms()->in_fd, STDIN_FILENO);
	if (ms()->out_fd >= STDOUT_FILENO)
		dup2(ms()->out_fd, STDOUT_FILENO);
}

void	io_disconnect(int command_index)
{
	if (ms()->in_fd > STDIN_FILENO)
		close(ms()->in_fd);
	if (ms()->out_fd > STDOUT_FILENO)
		close(ms()->out_fd);
	if (command_index > 0)
		close(ms()->pipes[command_index - 1][READ_END]);
	if (!is_last_command(command_index))
		close(ms()->pipes[command_index][WRITE_END]);
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
}
