/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:28:29 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/13 20:05:50 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(struct s_env_var	*env)
{
	struct s_env_var *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
void	free_env_sorted(char **env)
{
	if (env)
	{
		int i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

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

void 	free_program(t_program *program)
{
	if (program->input)
	{
		free(program->input);
		program->input = NULL;
	}
	if (program->cmds)
		free_cmds(&program->cmds);
	if (program->env)
		free_env(program->env);
	if (program->env_sorted)
		free_env_sorted(program->env_sorted);
}
void 	free_program_continue(t_program *program)
{
	if (program->input)
	{
		free(program->input);
		program->input = NULL;
	}
	if (program->cmds)
		free_cmds(&program->cmds);
}
