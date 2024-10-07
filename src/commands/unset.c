#include "../../includes/minishell.h"

void free_node(t_env_var *node)
{
	if (node->content)
		free(node->content);
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	exec_unset(t_env_var **list, char *var)
{
	t_env_var	*temp;
	t_env_var	*prev;

	temp = *list;
	prev = NULL;
    while (temp != NULL)
    {
        if (ft_strncmp(temp->name, var, strlen(var) + 1) == 0)
        {
            if (prev == NULL) // Node to be deleted is the first node
            {
                *list = temp->next;
            }
            else // Node to be deleted is not the first node
            {
                prev->next = temp->next;
            }
            free_node(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

/* void	unset(t_data *data, t_env_var **list)
{
	int	i;

	i = 1;
	while (data->input[i])
	{
		exec_unset(list, data->input[i]);
		i++;
	}
} */

void	unset(cmd_list **cmd)
{
	int	i;

	i = 1;
	while ((*cmd)->content[i])
	{
		exec_unset(&(*cmd)->env, (*cmd)->content[i]);
		i++;
	}
}