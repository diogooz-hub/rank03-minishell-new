#include "../../includes/minishell.h"

void	cd_home(cmd_list *cmd)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) == -1)
			exec_cmd_error(cmd, "chdir");
	}
	else
		printf("HOME variable not set\n");
}

void	relative_path(cmd_list *cmd, char *dir)
{
	char	path_buf[PATH_MAX];
	char 	*final_path;

	if (getcwd(path_buf, sizeof(path_buf)) != NULL)
	{
		//printf("Current working dir: %s\n", path_buf);
		dir = ft_strjoin("/", dir);
		final_path = ft_strjoin(path_buf, dir);
		//printf("Final path: %s\n", final_path);
		if (chdir(final_path) == -1)
			exec_cmd_error(cmd, "chdir");
	}
	else
		perror("No such file or directory\n");
}

void	absolute_path(cmd_list *cmd, char 	*s)
{
	if (chdir(s) == -1)
		exec_cmd_error(cmd, "chdir");
}

void	cd(cmd_list **cmd)
{
	bool	full_path;

	if (!(*cmd)->content[1])
	{
		cd_home((*cmd));
		return ;
	}
	full_path = check_if_full_path((*cmd)->content[1]);
	if ((*cmd)->content && !full_path)
		relative_path((*cmd), (*cmd)->content[1]);
	else if ((*cmd)->content && full_path)
		absolute_path((*cmd), (*cmd)->content[1]);
}