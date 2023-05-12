/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/10 11:25:33 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment(t_token *token)
{
	int	i;

	i = -1;
	if (token->str[0])
	{
		if (token->str[0] == '='
			|| token->str[ft_strlen(token->str) - 1] == '=')
		{
			error(ANSI_RED, ERROR_BAD_ASSIGNMENT, NULL, 1);
			return (false);
		}
	}
	while (token->str[++i])
	{
		if (token->str[i] == '=')
		{
			export_directly(&ms()->envtmp, token->str);
			return (true);
		}
	}
	return (false);
}

char	*_update_prompt(void)
{
	char	*tmp;
	char	*prompt;
	char	*prefix;
	char	*suffix;

	prefix = ANSI_BOLD""ANSI_WHITE""PROMPT_UPPER""ANSI_UNDERLINE""ANSI_CYAN;
	suffix = ANSI_RST"\n"ANSI_WHITE""PROMPT_LOWER""ANSI_RST;
	tmp = ft_strjoin(prefix, ms()->cwd);
	prompt = ft_strjoin(tmp, suffix);
	free(tmp);
	return (prompt);
}

int	_compute(void)
{
	if (!lexical_analysis())
		return (0);
	lexer();
	if (!syntatic_analysis())
		return (0);
	expander();
	parser();
	if (!is_assignment(ms()->lexemes->content))
		execute(ms()->ast);
	update_envs();
	unlink(HEREDOC);
	return (0);
}

void	reader(void)
{
	while (1)
	{
		(ms()->prompt) = _update_prompt();
		(ms()->input) = readline(ms()->prompt);
		if (!ms()->input)
		{
			printf("exit\n");
			sanitize(true);
		}
		add_history(ms()->input);
		_compute();
		sanitize(false);
	}
	rl_clear_history();
}
