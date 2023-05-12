/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:31:44 by crypto            #+#    #+#             */
/*   Updated: 2023/05/08 15:10:18 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_env_key_cmp(t_env *env, char *key)
{
	return (ft_strcmp(env->key, key) == 0);
}

void	ft_unset(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		ft_list_remove_if(&ms()->envlist, var[i], _env_key_cmp, env_destroy);
		ft_list_remove_if(&ms()->envtmp, var[i], _env_key_cmp, env_destroy);
	}
}
