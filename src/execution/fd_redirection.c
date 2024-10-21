/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:08:42 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 08:49:13 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_parent_pipe_ends(cmd_list *cmd)
{
	if (cmd->fd[1] != -1)
	{
		close(cmd->fd[1]);
		cmd->fd[1] = -1; // Reset to prevent accidental reuse
	}
	// Close read end of the previous command
	if (cmd->prev && cmd->prev->fd[0] != -1)
	{
		close(cmd->prev->fd[0]);
		cmd->prev->fd[0] = -1; // Reset to prevent accidental reuse
	}
}

void	close_child_pipe_ends(cmd_list *cmd)
{
	if (cmd->fd[0] != -1)
	{
		close(cmd->fd[0]);
		cmd->fd[0] = -1;
	}
	if (cmd->fd[1] != -1)
	{
		close(cmd->fd[1]);
		cmd->fd[1] = -1;
	}
}

void	close_pipe_ends(cmd_list *cmd, int is_parent)
{
    // Parent process should close the write end after forking
    if (is_parent)
		close_parent_pipe_ends(cmd);
    else // Child process should close all unused ends
		close_child_pipe_ends(cmd);
}

void setup_pipes(cmd_list *cmd)
{
    if (cmd->next)
    {
        if (pipe(cmd->fd) == -1)
        {
			exec_process_error(cmd, "pipe");
			return ;
        }
        cmd->fd_master[1] = cmd->fd[1];
        cmd->next->fd_master[0] = cmd->fd[0];
    }
}

void restore_fds(cmd_list *cmd, int og_stdin, int og_stdout)
{
	if (cmd->fd_master[0] != STDIN_FILENO)
	{
		if (dup2(og_stdin, STDIN_FILENO) == -1)
		{
			exec_process_error(cmd, "dup2");
			return ;
		}
		close(og_stdin);
	}
	if (cmd->fd_master[1] != STDOUT_FILENO)
	{
		if (dup2(og_stdout, STDOUT_FILENO) == -1)
		{
			exec_process_error(cmd, "dup2");
			return ;
		}
		close(og_stdout);
	}
}


void execute_redirections(cmd_list *cmd)
{
    if (cmd->fd_master[0] != STDIN_FILENO)
    {
        if (dup2(cmd->fd_master[0], STDIN_FILENO) == -1)
        {
			exec_process_error(cmd, "dup2");
			return ;
        }
        close(cmd->fd_master[0]);
    }
    if (cmd->fd_master[1] != STDOUT_FILENO)
    {
		//printf("duplicating output file descriptor for output\n");
        if (dup2(cmd->fd_master[1], STDOUT_FILENO) == -1)
        {
			exec_process_error(cmd, "dup2");
			return ;
        }
        close(cmd->fd_master[1]);
    }
	close_pipe_ends(cmd, 0);
}
