/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/08 20:02:46 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **tokens)
{
	int		i;

	i = 0;
	if (tokens[0] && !ft_strcmp(tokens[0], "-n"))
		i++;
	while (tokens[i])
	{
		printf("%s", tokens[i++]);
		if (tokens[i])
			printf(" ");
	}
	if (!tokens[0] || ft_strcmp(tokens[0], "-n") != 0)
		printf("\n");
}
