/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:31:58 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/01 19:19:13 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_error(t_list *cmd, char *error)
{
	(void)cmd;
	(void)error;
	//cmd not found
	//permission denied
	//is a directory
	//no such file or directory
}
