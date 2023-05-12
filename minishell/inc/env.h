/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:46:06 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:46:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "macros.h"

/**
 * @brief A struct to represent an environment variable.
 * 
 * @param key The name of the environment variable.
 * @param value The value of the environment variable.
 * 
 */
typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\ ENVLIST /=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Creates a new pointer to a new t_env struct.
 * 
 * @param key The name of the environment variable.
 * @param value The value of the environment variable.
 * @return t_env* A new pointer to the t_env struct.
 * @return NULL if malloc fails.
 */
t_env		*env_new(char *key, char *value);

/**
 * @brief Creates a new pointer to a duplicate of the env struct passed as
 * argument.
 * 
 * @param env The environment variable to duplicate.
 * @return t_env* A pointer to the duplicated environment variable.
 * @return NULL if malloc fails.
 */
t_env		*env_copy(t_env	*env);

/**
 * @brief Converts the environment variable list to a matrix so that
 * it can be used in the execve calls.
 * 
 * @param envlist The environment variable list.
 * @return char** A new pointer to the matrix of environment variables.
 * @return NULL if malloc fails.
 */
char		**envlist_to_matrix(t_list *envlist);

/**
 * @brief Frees the memory allocated to a t_env* struct.
 * 
 * @param env The t_env struct to free the memory of.
 */
void		env_destroy(t_env *env);

/**
 * @brief Called in the beginning of the program to create the environment
 * variable list. It uses the original environment variable matrix received
 * from the system.
 * 
 * @param envp The original environment variable matrix.
 * @return t_list* A new pointer to the list of environment variables.
 * @return NULL if malloc fails.
 */
t_list		*envlist(char **envp);

#endif