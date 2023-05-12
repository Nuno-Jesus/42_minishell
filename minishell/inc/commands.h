/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:48:07 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:48:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "macros.h"
# include "env.h"

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ CD /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Replica of the original cd command: changes the working directory
 * based on its arguments.
 * 
 * @param tokens The arguments of the command
 */
void		ft_cd(char **tokens);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ ECHO /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Replica of the original echo command: prints its arguments to the
 * shell, with a newline at the end. If the -n option is chosen, the newline 
 * won't be printed
 * 
 * @param tokens The arguments of the command
 */
void		ft_echo(char **tokens);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ ENV /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Prints all the declarations of variables, both exported and 
 * temporary in the format declare -x NAME="VALUE". 
 */
void		export_print_all(void);

/**
 * @brief Searches in the envlist for an environment variable that matches
 * the given key and returns its value.
 * 
 * @param key The name of the variable
 * @return char* A new pointer to the value of the variable or an empty string
 */
char		*get_env(char *key);

/**
 * @brief Replica of the original env command: displays all the environment
 * variables exported in the shell. For each variable composed of NAME and VALUE,
 * the printed format is NAME=VALUE.
 * 
 * @param tokens The arguments of the command
 */
void		ft_env(char **tokens);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ EXIT /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Given a string, this function checks if it is a valid number and fits
 * in the long long range.

 * @param num The string to check
 * @return true If the string fits in a long long
 * @return false Otherwise
 */
bool		_is_longlong(char *num);

/**
 * @brief Replica of the original exit command: terminates the execution of the
 * shell and sets the exit status according to its argument. If no argument is
 * given the default status will be 0.
 * 
 * @param tokens The arguments of the command
 */
void		ft_exit(char **tokens);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ EXPORT /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Like get_env, given a key it searches in the envlist passed as 
 * parameter for an environment variable that matches the key. If found,
 * it returns the pointer to the environment variable.
 * 
 * @param envlist The environment variable list to search on
 * @param key The key to match
 * @return t_env* A pointer to the environment variable
 * @return NULL If the variable is not found
 */
t_env		*_env_find(t_list *envlist, char *key);

/**
 * @brief A helper of the export function: given a name, it searches in the 
 * temporary environment variable list for the variable. If found, it exports
 * to the envlist.
 * 
 * @param name The name of the variable to search for
 */
void		_export_from_temp_list(char *name);

/**
 * @brief A helper of the export function: given the string containing an 
 * assignment, it splits the string into NAME and VALUE and creates a new
 * environment variable node to export to the envlist passed as parameter.
 * 
 * @param envlist The environment variable list to export to
 * @param assignment The string containing the assignment
 */
void		export_directly(t_list **envlist, char *assignment);

/**
 * @brief A replica of the original export command: given a list of its
 * arguments, it creates new environment variables and exports them to the
 * environment variable list. If no arguments are given, it displays all 
 * the environment variables exported in the shell.
 * 
 * @param tokens The arguments of the command
 */
void		ft_export(char **tokens);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ UNSET /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief A helper of the unset function: given the name of an environment 
 * variable, it returns the result of the comparison of the key of the 
 * variable with the name.
 * 
 * @param env The environment variable to compare
 * @param key The name to compare with
 * @return true If the names match
 * @return false Otherwise
 */
bool		_env_key_cmp(t_env *env, char *key);

/**
 * @brief A replica of the original unset command: given a list of its
 *arguments, it removes the variables passed as parameters in the 
 * environment variable list.
 * 
 * @param tokens 
 */
void		ft_unset(char **tokens);

#endif