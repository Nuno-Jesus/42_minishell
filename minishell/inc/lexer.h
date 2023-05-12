/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:36:33 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:36:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "macros.h"

/**
 * @brief An enum struct representing the different types of lexemes
 * recognized by the lexer. The lexer will use this enum to determine
 * when to split the input string into tokens.
 * 
 */
typedef enum e_lexeme
{
	LEX_IN_1,
	LEX_OUT_1,
	LEX_IN_2,
	LEX_OUT_2,
	LEX_PIPE,
	LEX_SINGLE_QUOTES,
	LEX_DOUBLE_QUOTES,
	LEX_TERM,
}	t_lexeme;

typedef struct s_token
{
	char			*str;
	bool			can_merge;
	t_lexeme		type;
}	t_token;

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= ANALYSIS =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Ensures the raw input string is valid to be parsed. This steps 
 * takes into account misconfigurations like a blank string or unclosed
 * quotes, which could crash the lexer.
 * 
 * @return true If the string is well configured
 * @return false Otherwise
 */
bool		lexical_analysis(void);

/**
 * @brief After the string has been tokenized, the syntatic analysis
 * has the role 
 * 
 * @return true 
 * @return false 
 */
bool		syntatic_analysis(void);

/**
* @brief 
* that are recognized by the lexer as a single unit. 
* @param str The string of characters that make up the token.
* @param type The type of lexeme that the token is.
*/

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= EXPANSION =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Iterates through the lexemes list to reduce the list to unmergeable
 * tokens. The list will be smaller or of the same size.
 * 
 * @param lexemes The lexemes list
 */
void		merge_lexemes(t_list *lexemes);

/**
 * @brief Responsible for findind the name of a environment variable in a
 * string. This function is only called if a $ sign is found in the string.
 * For instance, if the $PATH variable is in the string it will return
 * a new string containing "$PATH".
 * 
 * @param str The string to search for.
 * @return char* A new pointer to the environment variable name.
 */
char		*_find_key(char *str);

/**
 * @brief Given a token, this function iterates over the string to search
 * for $ signs and expand them into their respective environment variables
 * values. For instance, if $SHELL is set to "/bin/zsh" and found
 * on the string, $SHELL is replaced with "/bin/zsh".
 * @param token The token to parse the string on
 */
void		_expand_variable(t_token *token);

/**
 * @brief Iterates of the lexeme list and checks if the current lexeme is 
 * LEX_TERM or LEX_DOUBLE_QUOTES. If so, it calls _expand_variable() on the
 * token.
 */
void		expander(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ LEXER _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Verifies if a fresh token can be merged with the next. Looks ahead
 * in the raw input after the end of the token. Depending on the matches we
 * are looking for, we might need to check different conditions
 * 
 * @param str The input string
 * @param match The matches we are looking for
 * @param jump The len of the token
 * @return true If the token is mergeable
 * @return false Otherwise
 */
bool		_is_mergeable(char *str, char *match, int jump);

/**
 * @brief Given a string and a type of lexeme, it creates a new pointer to
 * a t_token and pushes it to the lexeme list.
 * 
 * @param str The string of the token.
 * @param lexeme The type of lexeme that the token is.
 * @param is_joinable A boolean that indicates if the token is joinable.
 * @return int The number of characters to skip in the input string.
 */
int			_lexer_push_token(char *str, t_lexeme lexeme, bool can_merge);

/**
 * @brief This function is set to find the match of a quote in string.
 * For instance, if the string is "Hello world", it will return the index
 * of the second quote. Also, if the symbols is set to SYMBOLS (defined in
 * macros.h), it will return the index of the first symbol found in the 
 * string. It also creates a new token out of it.
 * 
 * @param symbols The symbols to search for.
 * @param input The raw input string.
 * @return int The number of characters to skip in the input string.
 */
int			_lexer_find_match(char *symbols, char *input);

/**
 * @brief The lexer is one of the components of the shell. It is responsible
 * for splitting the input string into tokens. For instance, the string 
 * "ls > file" will be split into three tokens: "ls", ">" and "file",
 * creating a list with this format:
 * 	
 * 			[ls] 		-> [>] 			-> [file]
 * 			[LEX_TERM]  -> [LEX_OUT_1]  -> [LEX_TERM]
 */
void		lexer(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ TOKEN _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Creates a new pointer to a t_token.
 * 
 * @param str The string of the token.
 * @param type The type of lexeme that the token is.
 * @param is_joinable A boolean that indicates if the token is joinable.
 * @return t_token* A pointer to new t_token struct.
 * @return NULL If the allocation fails.
 */
t_token		*token_new(char *str, t_lexeme type, bool is_joinable);
/**
 * @brief Creates a new pointer to a copy of the token passed as argument.
 * 
 * @param token The token to copy
 * @return t_token* A pointer to the new t_token struct.
 * @return NULL If the allocation fails.
 */
t_token		*token_copy(t_token *token);

/**
 * @brief Frees the memory allocated for the token.
 * 
 * @param token The token to destroy.
 */
void		token_destroy(t_token *token);

#endif