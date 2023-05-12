/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/10 09:54:10 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

void	update_envs(void)
{
	char	*tmp;

	matrix_destroy(ms()->path);
	matrix_destroy(ms()->envp);
	tmp = get_env("PATH");
	(ms()->path) = ft_split(tmp, ':');
	(ms()->envp) = envlist_to_matrix(ms()->envlist);
	free(tmp);
}

void	sanitize(bool end)
{
	ft_free(ms()->input);
	ft_free(ms()->prompt);
	ast_clear(ms()->ast, ast_destroy_node);
	matrix_destroy(ms()->pipes);
	ft_lstclear(&ms()->lexemes, (void (*)(void *))token_destroy);
	(ms()->ast) = NULL;
	(ms()->pipes) = NULL;
	(ms()->prompt) = NULL;
	(ms()->lexemes) = NULL;
	(ms()->num_commands) = 0;
	if (end)
	{
		ft_free(ms()->cwd);
		matrix_destroy(ms()->path);
		matrix_destroy(ms()->envp);
		ft_lstclear(&ms()->envlist, (void (*)(void *))env_destroy);
		ft_lstclear(&ms()->envtmp, (void (*)(void *))env_destroy);
		exit(ms()->exit_status);
	}
}
