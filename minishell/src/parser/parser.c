/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:33:50 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:33:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*_extend_command(t_ast *command)
{
	t_ast	*redir;

	redir = ast_new(token_copy(scanner(READ)));
	if (!redir)
		return (NULL);
	scanner(NEXT);
	redir->args = matrix_append(redir->args, ft_strdup(scanner(READ)->str));
	redir->left = command->left;
	command->left = redir;
	return (command);
}

t_ast	*_extend_pipeline(t_ast *ast, t_ast *command)
{
	t_ast	*root;

	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE, false));
	if (!root)
		return (NULL);
	ast_insert(&root, ast, true);
	ast_insert(&root, command, false);
	return (root);
}

t_ast	*_parse_command(void)
{
	t_ast	*cmd;

	cmd = ast_new(token_copy(scanner(READ)));
	if (!cmd)
		return (NULL);
	cmd->index = ms()->num_commands++;
	while (scanner(READ) && scanner(READ)->type != LEX_PIPE)
	{
		if (scanner(READ)->type >= LEX_IN_1 && scanner(READ)->type <= LEX_OUT_2)
			cmd = _extend_command(cmd);
		else
			cmd->args = matrix_append(cmd->args, ft_strdup(scanner(READ)->str));
		scanner(NEXT);
	}
	return (cmd);
}

t_ast	*_parse_pipeline(void)
{
	t_ast	*ast;
	t_ast	*command;

	command = NULL;
	ast = _parse_command();
	if (!ast)
		return (NULL);
	while (scanner(READ) && scanner(READ)->type == LEX_PIPE)
	{
		scanner(NEXT);
		command = _parse_command();
		ast = _extend_pipeline(ast, command);
	}
	return (ast);
}

void	parser(void)
{
	scanner(RESET);
	ms()->ast = _parse_pipeline();
}
