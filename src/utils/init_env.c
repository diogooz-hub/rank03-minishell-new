#include "../../includes/minishell.h"

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

	copy_array_to_list(program->init_env, &program->env);
	temp = program->env;
	while (temp)
	{
		parse_name_value(temp);
		temp = temp->next;
	}
}