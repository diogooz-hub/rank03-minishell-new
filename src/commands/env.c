#include "../../includes/minishell.h"

void	env(cmd_list **cmd)
{
	t_env_var	*temp;

	if ((*cmd)->content[1])
	{
		printf("subject says: env should not have arguments or options\n");
		set_exit_status(*cmd, 1);
		return ;
	}
	temp = (*cmd)->prog->env_list;
	while (temp)
	{
		if (temp->value)
			printf("%s\n", temp->var);
		temp = temp->next;
	}
}
