#include "../../includes/minishell.h"

/*
t_env_var	*ft_lstnew_minish(char *var)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
		return (0);
	new -> var = var;
	new -> next = NULL;
	return (new);
}

void	ft_lstadd_back_minish(t_env_var **lst, t_env_var *new)
{
	t_env_var	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp -> next != NULL)
	{
		temp = temp -> next;
	}
	temp -> next = new;
}

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
*/

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

/*
void	copy_array_to_list(char **arr, t_env_var **list)
{
	int			i;
	t_env_var	*node;

	i = 0;
	while (arr[i])
	{
		node = ft_lstnew_minish(arr[i]);
		ft_lstadd_back_minish(list, node);
		i++;
	}
}
*/

void	update_env_array(char ***env_array, t_env_var **env_list)
{
	int			size;
	t_env_var	*temp;
	int			i;

	size = ft_lstsize_minish(env_list);
	//free the previous array
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