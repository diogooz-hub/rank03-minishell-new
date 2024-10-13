/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:31:58 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/13 20:11:44 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_error(cmd_list *cmd, char *error)
{
	if (!strcmp(error, "fork"))
	{
		printf("Error: fork failed\n");
		set_exit_status(cmd, 1);
	}
	else if (!strcmp(error, "execution"))
	{
		printf("Error: execution failed\n");
		set_exit_status(cmd, 1);
	}
	else if (!strcmp(error, "pipe"))
	{
		printf("Error: pipe failed\n");
		set_exit_status(cmd, 1);
	}
	else if (!strcmp(error, "dup2"))
	{
		printf("Error: dup2 failed\n");
		set_exit_status(cmd, 1);
	}
	else if (!strcmp(error, "default_exec"))
	{
		printf("minishell: %s: command not found\n", cmd->content[0]);
		set_exit_status(cmd, 127);
	}
	else if (!strcmp(error, "getcwd"))
	{
		printf("Error: getcwd failed\n");
		set_exit_status(cmd, 1);
	}
	else if (!strcmp(error, "chdir"))
	{
		printf("Error: chdir failed\n");
		set_exit_status(cmd, 1);
	}
}
