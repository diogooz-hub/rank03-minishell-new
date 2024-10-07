/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:28:29 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/01 19:49:56 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	free_env(struct s_env_var	*env)
{
}
*/

void 	free_cmds(cmd_list **cmds)
{
    cmd_list *tmp;
    while (*cmds) {
        tmp = *cmds;
        *cmds = (*cmds)->next;
        free(tmp->content);
        free(tmp->path);
        free(tmp);
    }
    *cmds = NULL;
}

void 	free_program(t_program program)
{
	free_cmds(&program.cmds);
	free(program.input);
	program.input = NULL;
	//free_env(&program.env);
	//free_env(&program.env_sorted);
	//exit(0);
}
