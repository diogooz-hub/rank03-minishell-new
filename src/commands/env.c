#include "../../includes/minishell.h"

void	env(cmd_list **cmd)
{
	t_env_var	*temp;

	temp = (*cmd)->prog->env_list;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
}
