/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:49:36 by marvin            #+#    #+#             */
/*   Updated: 2023/05/09 10:49:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexical_analysis(void)
{
	int		i;
	char	quote;
	bool	in_quotes;

	i = -1;
	quote = '\"';
	in_quotes = false;
	if (is_spaces(ms()->input))
		return (false);
	while (ms()->input[++i])
	{
		if (in_quotes && ms()->input[i] == quote)
			in_quotes = false;
		else if (!in_quotes && ft_strchr("\"\'", ms()->input[i]))
		{
			quote = ms()->input[i];
			in_quotes = true;
		}
	}
	if (in_quotes)
		return (error(ANSI_RED, ERROR_UNCLOSED_QUOTES, NULL, 2));
	return (true);
}

bool	syntatic_analysis(void)
{
	t_token	*next;
	int		num_pipes;
	int		num_commands;

	num_pipes = 0;
	num_commands = 1;
	scanner(RESET);
	if (is_redir_or_pipe(scanner(READ)))
		return (error(ANSI_RED, ERROR_SYNTAX, scanner(READ)->str, 2));
	while (scanner(READ))
	{
		next = scanner(LOOKAHEAD);
		if (is_redirection(scanner(READ)) && (!next || is_redir_or_pipe(next)))
			return (error(ANSI_RED, ERROR_UNCLOSED_RED, NULL, 2));
		if (scanner(READ)->type == LEX_PIPE)
		{
			num_pipes++;
			if (next && !is_redir_or_pipe(next))
				num_commands++;
		}
		scanner(NEXT);
	}
	if (num_pipes >= num_commands)
		return (error(ANSI_RED, ERROR_UNCLOSED_PIPES, NULL, 2));
	return (true);
}
