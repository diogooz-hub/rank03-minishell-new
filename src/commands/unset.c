#include "../../includes/minishell.h"

void free_node(t_env_var *node)
{
	if (node->var)
		free(node->var);
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

void	unset(cmd_list **cmd)
{
	int	i;

	i = 1;
	//printf("unset check\n");
	while ((*cmd)->content[i])
	{
		exec_unset(&(*cmd)->prog->env_list, (*cmd)->content[i]);
		i++;
	}
	update_env_array(&(*cmd)->prog->env_array, &(*cmd)->prog->env_list);
}