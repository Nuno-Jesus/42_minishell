/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:12:35 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/08 08:45:10 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_create(void)
{
	int	i;

	(ms()->pipes) = ft_calloc(ms()->num_commands, sizeof(int *));
	if (!ms()->pipes)
		return ;
	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		(ms()->pipes[i]) = ft_calloc(2, sizeof(int));
		pipe(ms()->pipes[i]);
	}
}

void	pipeline_apply(int command_index)
{
	if (ms()->num_commands < 2)
		return ;
	if (ms()->in_fd == STDIN_FILENO)
		if (command_index != 0)
			ms()->in_fd = ms()->pipes[command_index - 1][READ_END];
	if (ms()->out_fd == STDOUT_FILENO)
		if (!is_last_command(command_index))
			ms()->out_fd = ms()->pipes[command_index][WRITE_END];
}

bool	is_last_command(int command_index)
{
	return (command_index == ms()->num_commands - 1);
}

bool	is_unforkable(char *command)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "exit") \
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset") \
		|| !ft_strcmp(command, "ptmp"));
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}
