/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:11:17 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 11:11:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "commands.h"
# include "env.h"
# include "macros.h"

/**
 * @brief Main structure of the program, used globally across the shell.
 *
 * @param in_fd			Standard input file descriptor used when redirecting
 * or piping
 * @param out_fd		Standard output file descriptor used when redirecting
 * or piping
 * @param exit_status	Exit status of the last command executed
 * @param num_commands	Number of commands in the pipeline
 * @param cwd			Current working directory
 * @param input			Input string of the command line
 * @param prompt		Prompt string of the command line
 * @param path			Environment variable PATH
 * @param envp			Matrix of environment variables
 * @param pipes			Matrix of pipes
 * @param envlist		Linked list of environment variables
 * @param envtmp		Linked list of temporary environment variables
 * @param lexemes		Linked list of lexemes
 * @param ast			Abstract Syntax Tree
 */
typedef struct s_ms
{
	int		in_fd;
	int		out_fd;
	int		exit_status;
	int		num_commands;
	bool	in_heredoc;
	char	*cwd;
	char	*input;
	char	*prompt;
	char	**path;
	char	**envp;
	int		**pipes;
	t_list	*envlist;
	t_list	*envtmp;
	t_list	*lexemes;
	t_ast	*ast;
}	t_ms;

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/ EXECUTION \_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Executes a command if it exists, otherwise does nothing and sets
 * the exit_status to 127.
 *
 * @param exe The name of the executable
 * @param argv The arguments of the command
 */
void		_execute_if_exists(char *exe, char **argv);

/**
 * @brief Given the arguments of a command and its name on argv[0], redirects
 * the program flow to the corresponding command.
 *
 * @param args The arguments of the command to execute
 */
void		_execute_command(char **args);

/**
 * @brief Executes a command that is not a builtin, by launching a new process.
 * It is responsible for handling redirections and pipes file descriptors to
 * ensure the continuity of IO.
 * @param node The ast node containing the command to execute
 */
pid_t		_execute_forkable(t_ast *node);

/**
 * @brief Recursively executes a pipeline of commands, by iterating down
 * the AST. If a redirections is found, the in_fd and out_fd are updated.
 * If a command is found, it is executed.
 *
 * @param node The starting node of the pipeline
 * @return pid_t The pid of the last command executed
 */
pid_t		_execute_pipeline(t_ast *node);

/**
 * @brief The base function to recursively execute an AST. Responsible to
 * set the exit status of the last command executed and await for the
 * commands to finish.
 *
 * @param ast The pipeline to execute
 * @return int The exit status of the last command executed
 */
void		execute(t_ast *ast);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ IO _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Changes the input and output file descriptors to the ones
 * setted in the ms struct. The fds might come from the pipeline
 * or redirections.
 */
void		io_connect(void);

/**
 * @brief Closes the input and output file descriptors. Uses the
 * command index passed as parameter to know which pipe to close.
 *
 * @param command_index The index of the command in the pipeline
 */
void		io_disconnect(int command_index);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ PATH _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Given the name of an executable, searches for it in the PATH
 * environment variable. If it is found, returns the full path to the
 * executable file.
 *
 * @param exe The name of the executable.
 * @return char* A string to absolute path to the executable file.
 * @return NULL If the executable is not found.
 */
char		*get_executable_path(char *exe);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= PIPELINE =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Generates a new matrix of pipes. The matrix is a 2D array of
 * integers, where each row represents a pipe. The first column is the
 * input file descriptor and the second column is the output file descriptor.
 */
void		pipeline_create(void);

/**
 * @brief If there is more than 1 command (pipeline) and there are no
 * redirections in the current command, it sets the IO according to the
 * fds in the current pipe
 *
 * @param command_index The index of the command in the pipeline
 */
void		pipeline_apply(int command_index);

/**
 * @brief Checks if the current command is the last command in the pipeline.
 *
 * @param command_index The index of the command
 * @return true If it is the last command
 * @return false Otherwise
 */
bool		is_last_command(int command_index);

/**
 * @brief Given a command name, checks if the command can be forked. In
 * A command is unforkable if its execution has to change the shell's
 * behaviour such as cd, export, etc.
 *
 * @param command The name of the command
 * @param arg The first argument appended with the command
 * @return true If the command is unforkable
 * @return false Otherwise
 */
bool		is_unforkable(char *command, char *arg);

/**
 * @brief Given a command name, checks if the command is a builtin.
 *
 * @param command The name of the command
 * @return true If the command is a builtin
 * @return false Otherwise
 */
bool		is_builtin(char *command);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_ REDIRECTIONS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Heredoc helper: the real reader of the heredoc functionality.
 * 
 * @param term The terminator of the heredoc.
 */
void		heredoc_reader(char *term);

/**
 * @brief Mimics the heredoc functionality of bash. It reads from stdin
 * until the terminator is found. The content is then written to a temporary
 * file and later linked to the input of the running command by setting
 * ms()->in_fd to the file descriptor of the temporary file.
 *
 * @param term The terminator of the heredoc.
 * @return int The file descriptor of the temporary file.
 * @return -1 If the heredoc could not be created.
 */
int			heredoc(char *term);

/**
 * @brief Given a redirection type and a filename, opens the file and
 * sets the corresponding file descriptor to the opened file.
 *
 * @param type The type of redirection
 * @param filename The name of the file (or the terminator in case of heredoc)
 */
void		execute_redirection(t_lexeme type, char *filename);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= HANDLERS =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Handles the SIGINT signal. If the signal is received while
 * the shell is waiting for a heredoc, it does nothing. Otherwise, it
 * prints a newline and refreshes the prompt.
 *
 * @param signum The signal number
 */
void		handler_sigint(int signum);

/**
 * @brief Handles the childs signals. If the signal is SIGINT, it
 * prints a newline and refreshes the prompt. If the signal is SIGQUIT,
 * it quits a hanging command.
 *
 * @param signum The signal number
 */
void		handler_child(int signum);

/**
 * @brief Handler of the heredoc SIGINT signal. Flushed all the allocated
 * child memory and exits the program
 * 
 * @param signum The signal number 
 */
void		handler_heredoc(int signum);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= SIGNALS =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Installs the signal handlers for SIGINT and SIGQUIT before
 * heredoc starts.
 */
void		signals_heredoc(void);

/**
 * @brief Installs the signal handlers for SIGINT and SIGQUIT before
 * the a child process is created.
 */
void		signals_child(void);

/**
 * @brief Installs the signal handlers for SIGINT and SIGQUIT before
 * the shell starts. It is also used to restore the original signal
 * handlers after calling signals_heredoc() and signals_child().
 */
void		signals(void);

/**
 * @brief After the heredoc child finished execution, this function is
 * called to prevent propagation of any signal to the parent process.
 * It ignores the possible signals temporarly.
 */
void		signals_ignore(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FAKE GLOBAL _/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Returns a pointer to the ms struct. The ms struct is called a
 * fake global since it consists of a static variable inside a function.
 *
 * @return t_ms* The pointer to the ms struct.
 */
t_ms		*ms(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= MATRIX =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Frees the memory allocated for a matrix. The last element
 * of the matrix must be NULL.
 *
 * @param matrix The matrix to free.
 */
void		matrix_destroy(void *matrix);

/**
 * @brief Returns the number of elements in a matrix. The last element
 * of the matrix must be NULL.
 *
 * @param mat The matrix to count the elements of.
 * @return size_t The number of elements in the matrix.
 */
size_t		matrix_size(char **mat);

/**
 * @brief Appends a string to a matrix. The last element of the matrix
 * must be NULL. It frees the resources associated with the original
 * matrix.
 *
 * @param m1 The matrix to append to.
 * @param str The string to append.
 * @return char** A pointer to the new matrix.
 * @return NULL If the allocation fails.
 */
char		**matrix_append(char **m1, char *str);

/**
 * @brief Duplicates a matrix. The last element of the matrix must be NULL.
 *
 * @param matrix The matrix to copy.
 * @return char** A pointer to new duplicated matrix.
 * @return NULL If the allocation fails.
 */
char		**matrix_copy(char **matrix);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= SANITIZE =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Free the memory allocated for a pointer if it is not NULL.
 *
 * @param p The pointer to free.
 */
void		ft_free(void *p);

/**
 * @brief Refreshed the minishell struct by reseting the values of
 * the variables. It also cleans the lexemes and the ast between each
 * prompt. If the end variable end is set to true, the memory related
 * to static variables is freed and the program ends.
 *
 * @param end If set to true, the program ends.
 */
void		sanitize(bool end);

/**
 * @brief Updates the environment variables. It is called after each
 * command execution.
 */
void		update_envs(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= UTILS =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Counts the number of chars in a string until a separator is
 * found. The separators are defined in the seps string.
 *
 * @param s The string to count the chars of.
 * @param seps The string containing the separators.
 * @return int The number of chars before the first separator.
 */
int			ft_strlen_sep(const char *s, char *seps);

/**
 * @brief Checks if a string is composed only of spaces.
 *
 * @param str The string to check
 * @return true If the string is composed only of spaces.
 * @return false Othwerwise
 */
bool		is_spaces(char *str);

/**
 * @brief Checks if the given token is a redirection
 *
 * @param token The token to check
 * @return true If the token is a redirection
 * @return false Otherwise
 */
bool		is_redirection(t_token *token);

/**
 * @brief Checks if the given token is a special token (redirection or pipe)
 *
 * @param token The token to check
 * @return true If the token is a special token
 * @return false Otherwise
 */
bool		is_redir_or_pipe(t_token *token);

/**
 * @brief Display an error message and sets the exit status of the minishell
 * to the status parameter.
 *
 * @param color The color of the message.
 * @param message The message to display.
 * @param param An optional parameter to display.
 * @param status The exit status of the minishell.
 * @return int A dummy return value.
 */
int			error(char *color, char *message, char *param, int status);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= DEBUG =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Prints the temporary variables of the minishell struct.
 */
void		tmp_debug(void);

/**
 * @brief Prints the content of a matrix.
 *
 * @param matrix The matrix to print.
 */
void		matrix_debug(char **matrix);

/**
 * @brief Prints the content of a token.
 *
 * @param token The token to print.
 */
void		token_debug(t_token *token);

/**
 * @brief Prints the contents of all lexemes formed by the lexer.
 */
void		lexer_debug(void);

/**
 * @brief Prints the contents of an ast, recursively.
 *
 * @param ast The ast to print.
 * @param depth The starting depth of the ast.
 * @param f The function to print the content of a node.
 */
void		ast_debug(t_ast *ast, int depth, void (*f)());

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= INPUT =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Given a token of the lexeme list, it takes the lexeme string and 
 * checks if the string is formatted as NAME=VALUE (is an assignment). 
 * If it is, it exports the token as a temporary environment variable.
 * 
 * @param token The token to check
 * @return true If the token is an assignment
 * @return false Otherwise
 */
bool		is_assignment(t_token *token);
/**
 * @brief Updates the prompt of the minishell struct. It is called
 * after each command execution so that it contains the current working
 * directory.
 *
 * @return char* The new prompt.
 */
char		*_update_prompt(void);

/**
 * @brief The newly read line is processed by the 3 most important functions
 * called by this one : lexer, expander and parser.
 * @return int A dummy return value.
 */
int			_compute(void);

/**
 * @brief Reads a line from the standard input and stores it in the
 * minishell struct.
 */
void		reader(void);

//! Main
/**
 * @brief Initializes the minishell struct. Called once.
 * @param envp The original environment variables.
 */
void		_ms_init(char **envp);

#endif
