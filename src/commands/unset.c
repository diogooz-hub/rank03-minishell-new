#include "../../includes/minishell.h"

void	exec_unset(t_env_var **list, char *var)
{
	t_env_var	*temp;
	t_env_var	*prev;

	temp = *list;
	prev = NULL;
	//printf("var to unset: %s\n", var);
    while (temp != NULL)
    {
        if (ft_strncmp(temp->name, var, strlen(temp->name)) == 0)
        {
			//printf("found var to unset\n");
            if (prev == NULL) // Node to be deleted is the first node
                *list = temp->next;
            else // Node to be deleted is not the first node
                prev->next = temp->next;
            free_node(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

bool	valide_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", arg);
		return (false);
	}
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
			return (false);
		}
	}
	return (true);
}

void	unset(cmd_list **cmd)
{
	int	i;

	i = 1;
	//printf("unset check\n");
	while ((*cmd)->content[i])
	{
		if(!valide_unset_arg((*cmd)->content[i]))
			exec_cmd_error(*cmd, "unset");
		exec_unset(&(*cmd)->prog->env_list, (*cmd)->content[i]);
		i++;
	}
	update_env_array(&(*cmd)->prog->env_array, &(*cmd)->prog->env_list);
}