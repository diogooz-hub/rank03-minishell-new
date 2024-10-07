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

/*
void	env(t_data *data, t_env_var **env)
{
	t_env_var	*temp;

	temp = *env;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}
*/