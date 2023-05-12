/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:50:38 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 18:50:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_is_longlong(char *num)
{
	bool	is_negative;

	is_negative = false;
	if (!ft_isnum(num))
		return (false);
	if (num[0] == '-')
		is_negative = true;
	if (is_negative)
		num++;
	while (*num == '0')
		num++;
	if (ft_strlen(num) > 19)
		return (false);
	if (is_negative)
		return (ft_strncmp(num, "9223372036854775808", ft_strlen(num)) <= 0);
	else
		return (ft_strncmp(num, "9223372036854775807", ft_strlen(num)) <= 0);
}

void	ft_exit(char **tokens)
{
	char			*status;

	if (matrix_size(tokens) > 1)
	{
		error(ANSI_RED, ERROR_EXIT_MANY_ARGS, NULL, 1);
		return ;
	}
	status = tokens[0];
	if (status)
	{
		if (!_is_longlong(status))
			error(ANSI_RED, ERROR_EXIT_NO_NUM, NULL, 2);
		else
			(ms()->exit_status) = ft_atoi(status) % 256;
	}
	sanitize(true);
}
