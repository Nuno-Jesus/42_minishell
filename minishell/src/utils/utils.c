/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:41:55 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 16:06:36 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\f' && str[i] != '\n' \
			&& str[i] != '\r' && str[i] != '\t' \
			&& str[i] != '\v' && str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	ft_strlen_sep(const char *s, char *seps)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(seps, s[i]))
		i++;
	return (i);
}

bool	is_redirection(t_token *token)
{
	return (token->type >= LEX_IN_1 && token->type <= LEX_OUT_2);
}

bool	is_redir_or_pipe(t_token *token)
{
	return (token->type >= LEX_IN_1 && token->type <= LEX_PIPE);
}

int	error(char *color, char *message, char *param, int status)
{
	if (param)
		printf("%s%s%s%s\n", color, message, param, ANSI_RST);
	else
		printf("%s%s%s\n", color, message, ANSI_RST);
	(ms()->exit_status) = status;
	return (0);
}
