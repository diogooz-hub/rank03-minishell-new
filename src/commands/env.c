#include "../../includes/minishell.h"

void	env(cmd_list **cmd)
{
	t_env_var	*temp;

	temp = (*cmd)->env;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}
