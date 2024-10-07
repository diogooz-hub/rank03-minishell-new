#include "../../includes/minishell.h"

void	pwd(cmd_list **cmd)
{
	char	path_buf[PATH_MAX];

	(void)cmd;
	if (getcwd(path_buf, sizeof(path_buf)) != NULL)
		printf("%s\n", path_buf);
	else
		perror("Error getting directory\n");
		//exec_error(cmd, "getcwd");
}
