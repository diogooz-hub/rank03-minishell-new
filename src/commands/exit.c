#include "../../includes/minishell.h"

void	exit_shell(cmd_list **cmd)
{
	free_program((*cmd)->prog);
	exit(EXIT_SUCCESS);
}