/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:22:54 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/01 19:19:43 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_temp_file(cmd_list *cmd, char *tmp_file)
{
	int		tmp_fd;

	tmp_fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		set_exit_status(cmd, 1);
		perror("error 4 on redirection");
		exit(1);
	}
	return (tmp_fd);
}

void	write_on_temp_file(int tmp_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
}

void	heredoc_redirection(cmd_list *cmd, char *delimiter)
{
	char	*tmp_file;
	int		tmp_fd;

	tmp_file = ft_strdup("/tmp/minishell_heredoc");
	tmp_fd = create_temp_file(cmd, tmp_file);
	write_on_temp_file(tmp_fd, delimiter);
	tmp_fd = open(tmp_file, O_RDONLY);
	if (tmp_fd == -1)
	{
		set_exit_status(cmd, 1);
		perror("error opening heredoc tmp file");
		exit(1);
	}
	cmd->fd_master[0] = tmp_fd;
	free(tmp_file);
}

void	input_redirection(cmd_list *cmd, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		set_exit_status(cmd, 1);
		perror("error 1 on redirection");
		exit(1);
	}
	cmd->fd_master[0] = fd;
}

void	output_redirection(cmd_list *cmd, char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		set_exit_status(cmd, 1);
		perror("error 2 on redirection");
		exit(1);
	}
	cmd->fd_master[1] = fd;
}

void	append_redirection(cmd_list *cmd, char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		set_exit_status(cmd, 1);
		perror("error 3 on redirection");
		exit(1);
	}
	cmd->fd_master[1] = fd;
}

void	set_file_descriptors(t_token **tokens, int *i, cmd_list *cmd)
{
	if (!strcmp(tokens[*i]->content, "<"))
		input_redirection(cmd, tokens[++(*i)]->content);
	else if (!strcmp(tokens[*i]->content, ">"))
		output_redirection(cmd, tokens[++(*i)]->content);
	else if (!strcmp(tokens[*i]->content, ">>"))
		append_redirection(cmd, tokens[++(*i)]->content);
	else if (!strcmp(tokens[*i]->content, "<<"))
		heredoc_redirection(cmd, tokens[++(*i)]->content);
}
