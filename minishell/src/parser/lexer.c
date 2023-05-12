/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/10 11:31:42 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_is_mergeable(char *str, char *match, int jump)
{
	if (!str[jump])
		return (false);
	if (!ft_strcmp(SYMBOLS, match) && ft_strchr(QUOTES, str[jump]))
		return (true);
	if (ft_strchr(QUOTES, match[0]) && !ft_strchr(SPECIAL, str[jump + 1]))
		return (true);
	return (false);
}

int	_lexer_push_token(char *str, t_lexeme lexeme, bool can_merge)
{
	t_token	*token;

	token = token_new(str, lexeme, can_merge);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

int	_lexer_find_match(char *match, char *input)
{
	int		jump;
	char	*token;
	bool	can_merge;

	jump = ft_strlen_sep(input, match);
	can_merge = _is_mergeable(input, match, jump);
	token = ft_substr(input, 0, jump);
	if (match[0] == '"')
		_lexer_push_token(token, LEX_DOUBLE_QUOTES, can_merge);
	else if (match[0] == '\'')
		_lexer_push_token(token, LEX_SINGLE_QUOTES, can_merge);
	else
		_lexer_push_token(token, LEX_TERM, can_merge);
	return (jump);
}

void	lexer(void)
{
	int	i;

	i = 0;
	while (ms()->input[i])
	{
		if (ms()->input[i] == ' ')
			i++;
		else if (ms()->input[i] == '|')
			i += _lexer_push_token(ft_strdup("|"), LEX_PIPE, false);
		else if (!ft_strncmp(&ms()->input[i], "<<", 2))
			i += _lexer_push_token(ft_strdup("<<"), LEX_IN_2, false);
		else if (!ft_strncmp(&ms()->input[i], ">>", 2))
			i += _lexer_push_token(ft_strdup(">>"), LEX_OUT_2, false);
		else if (ms()->input[i] == '<')
			i += _lexer_push_token(ft_strdup("<"), LEX_IN_1, false);
		else if (ms()->input[i] == '>')
			i += _lexer_push_token(ft_strdup(">"), LEX_OUT_1, false);
		else if (ms()->input[i] == '"')
			i += _lexer_find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += _lexer_find_match("'", &ms()->input[i + 1]) + 2;
		else
			i += _lexer_find_match(SYMBOLS, &ms()->input[i]);
	}
}

// printf("\n\t---------------------------\n\n");
// printf("input: %s\n", input);
// printf("input[%d]: '%c'\n", jump, input[jump]);
