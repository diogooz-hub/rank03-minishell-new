/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:39:36 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 08:49:16 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_on_parent(cmd_list *cmd, int og_stdin, int og_stdout)
{
	//printf("Executing command on parent\n");
	execute_redirections(cmd);
	cmd->ft_exec(&cmd);
	restore_fds(cmd, og_stdin, og_stdout);
}

void	child_exec(cmd_list *cmd, int og_stdin, int og_stdout)
{
	//printf("Executing command on child\n");
	execute_redirections(cmd);
	cmd->ft_exec(&cmd);
	restore_fds(cmd, og_stdin, og_stdout);
	exit(cmd->prog->exit_status);
}

void	parent_wait(pid_t pid, cmd_list *cmd)
{
	int status;
	int sign;

	//printf("[Parent] waiting for child to execute: %s\n", cmd->content[0]);
	waitpid(pid, &status, 0); // Wait for child process to finish
	if (WIFSIGNALED(status))
	{
		sign = WTERMSIG(status);
		if (sign == SIGINT)
			set_exit_status(cmd, 130);
		else
			set_exit_status(cmd, 128 + sign);
	}
	else if (WIFEXITED(status))
		set_exit_status(cmd, WEXITSTATUS(status));
	close_pipe_ends(cmd, 1);
}

void	command_on_child(cmd_list *cmd, int og_stdin, int og_stdout)
{
	pid_t pid;

	pid = fork();
	if (pid == 0) // Child process
		child_exec(cmd, og_stdin, og_stdout);
	else if (pid > 0) // Parent process
		parent_wait(pid, cmd);
	else
	{
		exec_process_error(cmd, "fork");
		return ;
	}
}
void	command_execution(cmd_list *cmd, int process_count)
{
	int og_stdin;
	int og_stdout;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	if (og_stdin == -1 || og_stdout == -1 || cmd->ft_exec == NULL)
	{
		set_exit_status(cmd, 1);
		exit(EXIT_FAILURE);
		exec_process_error(cmd, "execution");
		return ;
	}
	if (cmd->on_parent && process_count == 1)
		command_on_parent(cmd, og_stdin, og_stdout);
	else
		command_on_child(cmd, og_stdin, og_stdout);
}


void	execution(cmd_list *cmds)
{
	int cmd_count;

	cmd_count = 0;
    while (cmds)
    {
		cmd_count++;
        if (cmds->content[0])
        {
			//printf("Executing command: %s\n", cmds->content[0]);
			//expand_tokens(cmds);
			//printf("Expanded tokens\n");
            setup_pipes(cmds);
			set_exec(cmds);
            check_builtin(cmds);
			check_process(cmds);
            if (!cmds->built_in)
                cmds->path = find_path(cmds->prog->env_list, cmds->content[0]);
            command_execution(cmds, cmd_count);
        }
        cmds = cmds->next;
        //printf("Moving to next command\n");
    }
}

void executer (cmd_list *cmds)
{
	execution(cmds);
}