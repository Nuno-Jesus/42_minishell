/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:41:36 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "macros.h"
# include "lexer.h"

/**
 * @brief Operation to perform on the scanner
 */
typedef enum e_operation
{
	READ,
	NEXT,
	LOOKAHEAD,
	RESET
}	t_operation;

/**
 * @brief A structure to represent a node of an Abstract Syntax Tree
 * 
 * @param token The token associated with the node
 * @param args The arguments of the token
 * @param index Used if the token represents a command
 * @param left The left child of the node
 * @param right The right child of the node
 */
typedef struct s_ast
{
	t_token			*token;
	char			**args;
	int				index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//! _/=\_/=\_/=\_/=\_/=\_/ ABSTRACT SYNTAX TREE (AST) /=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Creates a new pointer to a node of an Abstract Syntax Tree.
 * 
 * @param token The token to link to the node.
 * @return t_ast* A pointer to the new created node.
 * @return NULL If the allocation failed.
 */
t_ast		*ast_new(t_token *token);

/**
 * @brief Inserts node in one of the children of ast. It does it in a
 * non-standard way, by assigning directly the node to the left or right,
 * instead of inserting it recursively.
 * 
 * @param ast The ast to insert the node in.
 * @param node The node to insert.
 * @param left If true, the node will be inserted in the left child of ast,
 * otherwise it will be inserted in the right child.
 */
void		ast_insert(t_ast **ast, t_ast *node, bool left);

/**
 * @brief Destroys a node of the ast by freeing the token and the arguments.
 * 
 * @param ast The node to destroy.
 */
void		ast_destroy_node(t_ast *ast);

/**
 * @brief Clears the ast by recursively freeing all the nodes.
 * 
 * @param ast The ast to clear.
 * @param del The function to use to free the nodes.
 */
void		ast_clear(t_ast *ast, void (*del)(t_ast *));

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ PARSER /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Extends a node representing a command, by creating and attaching
 * a node represening a redirection to it. It preserves the order of the 
 * redirections.
 * 
 * @param command The command to extend.
 * @return t_ast* The extended command.
 * @return NULL If the allocation failed.
 */
t_ast		*_extend_command(t_ast *command);

/**
 * @brief Links the old ast and the new command node by creating a new 
 * node represening a pipeline. It then assigns the left child of the 
 * pipeline to the old ast and the right to the new command.
 * 
 * @param ast The ast to link to the new command.
 * @param command The new command to link with the ast.
 * @return t_ast* A pointer to new ast
 * @return NULL If the allocation failed.
 */
t_ast		*_extend_pipeline(t_ast *ast, t_ast *command);

/**
 * @brief Parses a command by creating a node representing it and extending
 * it with redirections, if found along the way.
 * 
 * @return t_ast* A pointer to the new command node
 * @return NULL If the allocation failed. 
 */
t_ast		*_parse_command(void);

/**
 * @brief Parses a pipeline by creating a node representing it and extending
 * it with commands, if found along the way.
 * 
 * @return t_ast* A pointer to the new pipeline node, which represents 
 * the whole command line.
 */
t_ast		*_parse_pipeline(void);

/**
 * @brief After the lexer has tokenized the input, the parser will create
 * an Abstract Syntax Tree (AST) by parsing the tokens. The AST has the 
 * purpose of representing the command line in a more convenient way,
 * and assigning priorities to the tokens.
 * 
 * The parser makes use of a scanner to iterate through the tokens, retrieve
 * and parse them.
 */
void		parser(void);

//! Scanner
/**
 * @brief The scanner is used by the parser to iterate through the tokens
 * and retrieve them. It is used to keep track of which tokens have been 
 * analyzed and dealt with. The scanner supports three operations:
 * - READ: Reads the current token and returns it.
 * - NEXT: Moves to the next one.
 * - RESET: Resets the scanner to the first token.
 * 
 * @param op The operation to perform.
 * @return t_token* The token retrieved by the READ operation.
 * @return NULL If the operation is NEXT or the scanner has reached the end
 * of the tokens.
 */
t_token		*scanner(t_operation op);

#endif