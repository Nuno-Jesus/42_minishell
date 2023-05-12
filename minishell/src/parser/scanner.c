/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:35:01 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:35:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*scanner(t_operation op)
{
	static t_list	*current = NULL;

	if (op == READ && current)
		return (current->content);
	else if (op == RESET)
		current = ms()->lexemes;
	else if (op == NEXT)
		current = current->next;
	else if (op == LOOKAHEAD && current->next)
		return (current->next->content);
	return (NULL);
}
