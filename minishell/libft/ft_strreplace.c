/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:33:17 by marvin            #+#    #+#             */
/*   Updated: 2023/05/06 18:33:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*ret;
	char	*tmp;
	char	*ptr;
	int		len;

	if (!str || !old || !new)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ptr = ft_strnstr(str, old, ft_strlen(str));
	if (!ptr)
		return (NULL);
	tmp = ft_substr(str, 0, ptr - str);
	ft_strlcat(ret, tmp, len + 1);
	ft_strlcat(ret, new, len + 1);
	ft_strlcat(ret, ptr + ft_strlen(old), len + 1);
	ft_free(tmp);
	return (ret);
}
