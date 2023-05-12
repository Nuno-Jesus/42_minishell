/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:40:47 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/09 11:24:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *str, t_lexeme type, bool is_joinable)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->can_merge = is_joinable;
	return (token);
}

t_token	*token_copy(t_token *token)
{
	t_token	*dup;

	dup = token_new(ft_strdup(token->str), token->type, token->can_merge);
	if (!dup)
		return (NULL);
	return (dup);
}

void	token_destroy(t_token *token)
{
	if (!token)
		return ;
	ft_free(token->str);
	ft_free(token);
}
