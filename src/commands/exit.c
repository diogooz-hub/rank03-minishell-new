#include "../../includes/minishell.h"

void	exit_shell(cmd_list **cmd)
{
	(void)cmd;
	//funtion to free all the memory
	exit(0);
}