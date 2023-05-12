/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:45:03 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 12:45:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(char *input)
{
	char	*expanded;
	char	*value;
	char	*key;
	char	*tmp;

	expanded = ft_strdup(input);
	while (ft_strnstr(expanded, "$", ft_strlen(expanded)))
	{
		key = _find_key(expanded);
		if (!ft_strcmp(key, "$?"))
			value = ft_itoa(ms()->exit_status);
		else
			value = get_env(key);
		tmp = expanded;
		expanded = ft_strreplace(expanded, key, value);
		ft_free(tmp);
		ft_free(value);
		ft_free(key);
	}
	ft_free(input);
	return (expanded);
}

// n = ft_strlen(input);
// input[n] = '\n';
// if (write(fd, input, n + 1) == -1)
// {
// 	ft_free(input);
// 	close(fd);
// 	return (-1);
// }

void	heredoc_reader(char *term)
{
	int		fd;
	char	*input;

	fd = open(HEREDOC, O_WRONLY | O_CREAT | O_APPEND, 0666);
	while (1)
	{
		input = readline("heredoc > ");
		if (!input)
		{
			printf("\n");
			break ;
		}
		else if (input && !ft_strcmp(input, term))
		{
			ft_free(input);
			break ;
		}
		input = expand_heredoc(input);
		ft_putendl_fd(input, fd);
		ft_free(input);
	}
	close(fd);
	sanitize(true);
}

int	heredoc(char *term)
{
	signals_heredoc();
	if (ms()->in_fd > STDIN_FILENO)
		close(ms()->in_fd);
	if (!fork())
		heredoc_reader(term);
	signals_ignore();
	waitpid(0, NULL, 0);
	signals();
	return (open(HEREDOC, O_RDONLY));
}

void	execute_redirection(t_lexeme type, char *filename)
{
	if (type == LEX_OUT_1)
		(ms()->out_fd) = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (type == LEX_OUT_2)
		(ms()->out_fd) = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (type == LEX_IN_1)
		(ms()->in_fd) = open(filename, O_RDONLY);
	else if (type == LEX_IN_2)
		(ms()->in_fd) = heredoc(filename);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
		error(ANSI_RED, ERROR_UNKNOWN_FILE, filename, 1);
}
