/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:19 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:13:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_new(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->args = ft_calloc(1, sizeof(char *));
	return (node);
}

void	ast_insert(t_ast **ast, t_ast *node, bool left)
{
	if (*ast && left)
		(*ast)->left = node;
	else if (*ast && !left)
		(*ast)->right = node;
	else
		*ast = node;
}

void	ast_destroy_node(t_ast *ast)
{
	token_destroy(ast->token);
	matrix_destroy(ast->args);
}

void	ast_clear(t_ast *ast, void (*del)(t_ast *))
{
	if (!ast)
		return ;
	ast_clear(ast->left, del);
	ast_clear(ast->right, del);
	del(ast);
	ft_free(ast);
}
