/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:26:30 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/08 15:10:10 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key)
{
	t_env	*tmp;
	t_list	*curr;

	if (key[0] == '$')
		key++;
	curr = ms()->envlist;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

void	ft_env(char **tokens)
{
	t_list	*curr;
	t_env	*tmp;

	if (matrix_size(tokens) > 0)
	{
		error(ANSI_RED, ERROR_ENV_UNKNOWN_FILE, NULL, 127);
		return ;
	}
	curr = ms()->envlist;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		printf("%s=%s\n", tmp->key, tmp->value);
		curr = curr->next;
	}
}
