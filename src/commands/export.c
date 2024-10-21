/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:59:02 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/20 19:41:00 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_to_env_end(t_env_var **list, char *var)
{
	t_env_var	*new_node;
	t_env_var	*temp;

	new_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_node)
	{
		printf("Malloc failed\n");
		exit(-1);
	}
	new_node->var = ft_strdup(var);
	populate_env_node(new_node);
	new_node->next = NULL;
	temp = *list;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	new_node->prev = temp;
	temp->next = new_node;
}

void	sort_env_array(char **env_array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env_array[i])
	{
		j = i + 1;
		while (env_array[j])
		{
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
			{
				temp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_var_in_quotes(char *var)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	while (var[i]!= '\0' && var[i] != '=')
	{
		write(1, &var[i], 1);
		i++;
	}
	if (var[i] == '\0')
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, "=\"", 2);
	i++;
	while (var[i])
	{
		write(1, &var[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

bool	validate_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (false);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (false);
		}
		i++;
	}
	return (true);
}

void	export_with_args(cmd_list **cmd)
{
	char *var;
	int	i;

	i = 1;
	while ((*cmd)->content[i])
	{
		if(!validate_arg((*cmd)->content[i]))
			exec_error(*cmd, "export");
		i++;
	}
	i = 1;
	while ((*cmd)->content[i])
	{
		var = (*cmd)->content[i];
		printf("var to add: %s\n", var);
		if (var_exists(&(*cmd)->prog->env_list, var))
			exec_unset(&(*cmd)->prog->env_list, var);
		add_node_to_env_end(&(*cmd)->prog->env_list, var);
		i++;
	}
	update_env_array(&(*cmd)->prog->env_array, &(*cmd)->prog->env_list);
}

void	export_no_args(cmd_list **cmd)
{
	int	i;
	update_env_array(&(*cmd)->prog->env_array, &(*cmd)->prog->env_list);
	sort_env_array((*cmd)->prog->env_array);
	i = 0;
	while ((*cmd)->prog->env_array[i])
	{
		print_var_in_quotes((*cmd)->prog->env_array[i]);
		i++;
	}
}
