/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:12 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 20:35:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

t_env	*env_copy(t_env	*env)
{
	t_env	*copy;

	copy = env_new(ft_strdup(env->key), ft_strdup(env->value));
	if (!copy)
		return (NULL);
	return (copy);
}

void	env_destroy(t_env *env)
{
	ft_free(env->key);
	ft_free(env->value);
	ft_free(env);
}

char	**envlist_to_matrix(t_list *envlist)
{
	t_env	*env;
	char	*tmp1;
	char	*tmp2;
	char	**matrix;

	matrix = ft_calloc(1, sizeof(char *));
	if (!matrix)
		return (NULL);
	while (envlist)
	{
		env = (t_env *)envlist->content;
		tmp1 = ft_strjoin(env->key, "=");
		tmp2 = ft_strjoin(tmp1, env->value);
		matrix = matrix_append(matrix, ft_strdup(tmp2));
		free(tmp1);
		free(tmp2);
		envlist = envlist->next;
	}
	return (matrix);
}

t_list	*envlist(char **envp)
{
	t_list	*envlist;
	int		i;

	i = matrix_size(envp);
	envlist = NULL;
	while (--i >= 0)
		export_directly(&envlist, envp[i]);
	return (envlist);
}
