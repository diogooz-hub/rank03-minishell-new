#include "../../includes/minishell.h"

//void	parse_vars(t_data *data, t_env_var **vars_env);

// Criar duas funçoes diferentes, uma para export sem arguments e uma para export com arguments

//Sort com array

/* void	sort_env(char **envir, int len)
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
				temp = envir[h];
				envir[h] = envir[h + 1];
				envir[h + 1] = temp;
			}
			h++;
		}
		i++;
	}
} */

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
	while (temp[i] != '=')
	{
		new[i] = temp[i];
		i++;
	}
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
		declare_x = ft_strjoin("declare -x ", (*cmd)->prog->env_sorted[i]);
		final_str = insert_quotes(declare_x, ft_strlen(declare_x));
		printf("%s\n", final_str);
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


/* void	parse_vars(t_data *data, t_env_var **vars_env)
{
	int	i;
	int	h;
	int	is_quote;

	i = 0;
	h = 0;
	is_quote = 0;
	while (data->str[i] != 32)
		i++;
	i++;
	h = i;
	while (data->str[i])
	{
		if (data->str[i] == 39 || data->str[i] == 34)
			is_quote++;
		
	}
} */

/* void	parse_vars(t_data *data, t_env_var **vars_env)
{
	t_env_var	*temp;
	int			i;

	temp = *vars_env;
	(void)data;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '=')
			{
				temp->value = ft_strdup(temp->content + i + 1);
			}
			i++;
		}
		temp = temp->next;
	}
} */