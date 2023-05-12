/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:04:44 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:04:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(char *exe)
{
	char	*tmp;
	char	*path;
	int		i;

	i = -1;
	if (exe[0] == '\0')
		return (NULL);
	if (access(exe, F_OK) == 0)
	{
		path = ft_strjoin("", exe);
		return (path);
	}
	while (ms()->path[++i])
	{
		tmp = ft_strjoin(ms()->path[i], "/");
		path = ft_strjoin(tmp, exe);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_relative_path(char *exe)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(ms()->cwd, "/");
	path = ft_strjoin(tmp, exe + 2);
	free(tmp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	if (access(exe, F_OK) == 0)
		return (ft_strdup(exe));
	return (NULL);
}

char	*get_executable_path(char *exe)
{
	char	*path;

	if (exe[0] == '.')
		path = get_relative_path(exe);
	else
		path = get_absolute_path(exe);
	return (path);
}
