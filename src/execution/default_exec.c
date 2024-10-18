/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:55:57 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/18 18:40:05 by dpaco            ###   ########.fr       */
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
	if (execve((*cmd)->path, (*cmd)->content, (*cmd)->prog->env_array) == -1)
	{
		exec_error(*cmd, "default_exec");
		return ;
	}
}

void	default_exec_bin(cmd_list **cmd)
{
	//printf("entered default execution\n");
	if (execve((*cmd)->content[0], (*cmd)->content, (*cmd)->prog->env_array) == -1)
	{
		exec_error(*cmd, "default_exec");
		return ;
	}
}