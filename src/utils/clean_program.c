/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:28:29 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 20:02:17 by dpaco            ###   ########.fr       */
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
		free(tmp->var);
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
void	free_env_sorted(char **env)
{
	//printf("free_env_sorted1\n");
	if (env)
	{
		int i = 0;
		while (env[i])
		{
			//printf("free(env[%s])\n", env[i]);
			//printf("free(env[%d])\n", i);
			free(env[i]);
			i++;
		}
		//printf("free(env)\n");
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
	//printf("free_program\n");
	if (program->input)
	{
	//	printf("free(program->input)\n");
		free(program->input);
		program->input = NULL;
	}
	//printf("free_cmds\n");
	if (program->cmds)
		free_cmds(&program->cmds);
	//printf("free_env\n");
	if (program->env_list)
		free_env(program->env_list);
	//printf("free_env_sorted\n");
	if (program->env_array)
		free_env_sorted(program->env_array);
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
