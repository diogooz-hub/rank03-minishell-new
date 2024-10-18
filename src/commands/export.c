#include "../../includes/minishell.h"

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
	while (var[i] != '=')
	{
		write(1, &var[i], 1);
		i++;
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

void	export_with_args(cmd_list **cmd)
{
	char *var;

	var = (*cmd)->content[1];
	add_node_to_env_end(&(*cmd)->prog->env_list, var);
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
	//print array mas a cada iteração chamo uma auxiliar que copia a str mete quotes para imprimir e depois dá free
}

/*
void	sort_env(char **envir, int len)
{
	int	i;
	int	h;
	char *temp;

	i = 0;
	while(i < len - 1)
	{
		h = 0;
		while (h < len - 1)
		{
			if (ft_strncmp(envir[h], envir[h + 1], ft_strlen(envir[h]) + ft_strlen(envir[h + 1])) > 0)
			{
				temp = ft_strdup(envir[h]);
				free(envir[h]);
				envir[h] = ft_strdup(envir[h + 1]);
				free(envir[h + 1]);
				envir[h + 1] = ft_strdup(temp);
				free(temp);
			}
			h++;
		}
		i++;
	}
}

char	*insert_quotes(char *env, int len)
{
	char 	*temp;
	char	*new;
	int		i;

	i = 0;
	temp = ft_strdup(env);
	free(env);
	new = (char *)malloc((len + 2) * sizeof(char));
	while (temp[i] != '\0' && temp[i] != '=')
	{
		new[i] = temp[i];
		i++;
	}
	if (temp[i] == '\0')
		return (new);
	new[i++] = '=';
	new[i++] = 34;
	while (temp[i - 1] != '\0')
	{
		new[i] = temp[i - 1];
		i++;
	}
	new[i] = 34;
	new[i + 1] = '\0';
	return (new);
}

void	export_no_args(cmd_list **cmd)
{
	int	i;
	char	*declare_x;
	char	*final_str;

	i = 0;
	(*cmd)->prog->env_sorted = copy_list_to_array(&(*cmd)->env);
	sort_env((*cmd)->prog->env_sorted, env_len((*cmd)->prog->env_sorted));
	while ((*cmd)->prog->env_sorted[i])
	{
		//printf("check\n");
		declare_x = ft_strjoin("declare -x ", (*cmd)->prog->env_sorted[i]);
		//printf("check2\n");
		final_str = insert_quotes(declare_x, ft_strlen(declare_x));
		printf("%s\n", declare_x);
		i++;
		free (final_str);
	}
	//free_arr(data->env);
}

void	add_var_to_env(char **arr, t_env_var **list)
{
	int			i;
	t_env_var	*node;

	i = 0;
	while (arr[i])
	{
		node = ft_lstnew_minish(arr[i]);
		parse_name_value(node);
		//printf("\n name is: %s \n value is %s \n content is %s\n", node->name, node->value, node->content);
		ft_lstadd_back_minish(list, node);
		i++;
	}
}

void	export_with_args(cmd_list **cmd)
{
	add_var_to_env((*cmd)->content + 1, &(*cmd)->env);
}

*/