/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:59:09 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/19 19:24:30 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_minish(t_env_var **lst)
{
	int		i;
	t_env_var	*current;

	i = 0;
	current = *lst;
	while (current != NULL)
	{
		i++;
		current = current -> next;
	}
	return (i);
}

int	env_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

/*
char	**copy_array(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(env_len(arr) * sizeof(char *));
	while (i < env_len(arr))
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
*/

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	update_env_array(char ***env_array, t_env_var **env_list)
{
	int			size;
	t_env_var	*temp;
	int			i;

	size = ft_lstsize_minish(env_list);
	free_arr(*env_array);
	*env_array = (char **)malloc((size + 1) * sizeof(char *));
	(*env_array)[size] = NULL;
	temp = *env_list;
	i = 0;
	while (i < size)
	{
		(*env_array)[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
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

/*
char	**copy_list_to_array(t_env_var **list)
{
	int			size;
	t_env_var	*temp;
	int			i;
	char		**array;

	size = ft_lstsize_minish(list);
	array = (char **)malloc((size + 1) * sizeof(char *));
	array[size] = NULL;
	temp = *list;
	i = 0;
	while (i < size)
	{
		array[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
	return (array);
}
*/