#include "../../includes/minishell.h"

bool check_if_full_path(char *s)
{
	if (s[0] == '/')
		return (true);
	return (false);
}

void	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) == -1)
			perror("Error");
			//exec_error(cmd, "chdir");
	}
	else
		printf("HOME variable not set\n");
}

void	relative_path(char *dir)
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
			perror("Error");
			//exec_error(cmd, "chdir");
	}
	else
		perror("No such file or directory\n");
}

void	absolute_path(char 	*s)
{
	if (chdir(s) == -1)
		perror("Error");
		//exec_error(cmd, "chdir");
}

void	cd(cmd_list **cmd)
{
	bool	full_path;

	full_path = check_if_full_path((*cmd)->content[1]);
	//if ((*cmd)->content && (*cmd)->content[1])
	//	cd_home();
	if ((*cmd)->content && !full_path)
		relative_path((*cmd)->content[1]);
	else if ((*cmd)->content && full_path)
		absolute_path((*cmd)->content[1]);
}