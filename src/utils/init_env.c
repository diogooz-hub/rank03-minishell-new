/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:29:32 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/18 18:41:12 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_envp_to_array(t_program *program, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	program->env_array = (char **)malloc((i + 1) * sizeof(char *));
	if (!program->env_array)
	{
		printf("Malloc failed\n");
		exit(-1);
	}
	i = 0;
	while (envp[i])
	{
		program->env_array[i] = ft_strdup(envp[i]);
		i++;
	}
	program->env_array[i] = NULL;
}

void	populate_env_node(t_env_var *node)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (node->var[i] && node->var[i] != '=')
		i++;
	node->name = (char *)malloc((i + 1) * sizeof(char));
	node->name[i] = '\0';
	while (n < i)
	{
		node->name[n] = node->var[n];
		n++;
	}
	if (node->var[n])
		node->value = ft_strdup(node->var + i + 1);
	else
		node->value = NULL;
}

t_env_var	*new_env_node(char *var)
{
	t_env_var	*new_node;

	new_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_node)
	{
		printf("Malloc failed\n");
		exit(-1);
	}
	new_node->var = ft_strdup(var);
	populate_env_node(new_node);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_env_node(t_env_var **list, t_env_var *new_node)
{
	t_env_var	*temp;

	temp = *list;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	generate_env_list(t_program *program)
{
	int	i;
	t_env_var	*new_node;

	i = 0;
	while (program->env_array[i])
	{
		new_node = new_env_node(program->env_array[i]);
		add_env_node(&program->env_list, new_node);
		i++;
	}
}

void	init_env(t_program *program, char **envp)
{
	copy_envp_to_array(program, envp);
	generate_env_list(program);
}

/*
void	parse_name_value(t_env_var *node)
{
	int			i;
	int			h;

	i = 0;
	h = 0;
	while (node->content[i] && node->content[i] != '=')
	{
		i++;
	}
	node->name = (char *)malloc((i + 1) * sizeof(char));
	node->name[i] = '\0';
	while (h < i)
	{
		node->name[h] = node->content[h];
		h++;
	}
	if (node->content[h])
		node->value = ft_strdup(node->content + i + 1);
	else
		node->value = NULL;
}

void	init_env(t_program *program)
{
	t_env_var	*temp;

	copy_array_to_list(program->init_env, &program->env_list);
	temp = program->env_list;
	while (temp)
	{
		parse_name_value(temp);
		temp = temp->next;
	}
}
*/