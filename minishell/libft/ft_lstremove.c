/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:41:49 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/04 09:54:12 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_remove_if_aux(t_list *node, void *ref, \
	bool (*cmp)(), void (*f)())
{
	t_list	*ret;

	if (!node)
		return (NULL);
	if ((*cmp)(node->content, ref))
	{
		ret = ft_list_remove_if_aux(node->next, ref, cmp, f);
		if (*f)
			(*f)(node->content);
		free(node);
	}
	else
	{
		ret = node;
		ret->next = ft_list_remove_if_aux(node->next, ref, cmp, f);
	}
	return (ret);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, \
	bool (*cmp)(), void (*free_fct)())
{
	if (!begin_list || !cmp)
		return ;
	*begin_list = ft_list_remove_if_aux(*begin_list, data_ref, cmp, free_fct);
}
