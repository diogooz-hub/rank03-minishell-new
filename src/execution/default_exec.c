/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:55:57 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/02 23:00:15 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
função que executa comandos que não são built-in
com o execve que já fizemos no pipex
*/
void	default_exec(cmd_list **cmd)
{
	//printf("entered default execution\n");
	if (execve((*cmd)->path, (*cmd)->content, (*cmd)->prog->init_env) == -1)
	{
		printf("minishell: %s: command not found\n", (*cmd)->content[0]);
		set_exit_status(*cmd, 127);
		//printf("exit status: %d\n", (*cmd)->prog->exit_status);
		//exit (127);
	}
}