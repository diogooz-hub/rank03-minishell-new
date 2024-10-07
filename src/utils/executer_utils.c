/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:17:51 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/01 19:18:15 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_env(char *env_name, t_env_var *env)
{
	while (env)
	{
		if (!strcmp(env->name, env_name))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*find_path(t_env_var *env, char *cmd)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	paths = ft_split(search_env("PATH", env), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK))
		{
			//set_exit_status(cmd, 127);
			break ;
		}
		free(path);
		path = NULL;
		i++;
	}
	free_arr(paths);
	return (path);
}
void	check_process(cmd_list *cmd)
{
	if (!cmd->content[0])
		return ;
	else if (!strcmp(cmd->content[0], "exit"))
		cmd->on_parent = true;
	else if (is_single_cmd(cmd->content[0], "export") && cmd->content[1])
		cmd->on_parent = true;
	else if (!strcmp(cmd->content[0], "export"))
		cmd->on_parent = true;
	else if (!strcmp(cmd->content[0], "unset"))
		cmd->on_parent = true;
	else if (!strcmp(cmd->content[0], "cd"))
		cmd->on_parent = true;
}

void	set_exec(cmd_list *cmd)
{
	if (!cmd->content[0])
		return ;
	else if (!strcmp(cmd->content[0], "exit"))
		cmd->ft_exec = exit_shell;
	else if (!strcmp(cmd->content[0], "clear"))
		cmd->ft_exec = clear;
	else if (!strcmp(cmd->content[0], "echo"))
		cmd->ft_exec = echo;
	else if (!strcmp(cmd->content[0], "pwd"))
		cmd->ft_exec = pwd;
	else if (!strcmp(cmd->content[0], "env"))
		cmd->ft_exec = env;
	else if (is_single_cmd(cmd->content[0], "export") && cmd->content[1])
		cmd->ft_exec = export_with_args;
	else if (!strcmp(cmd->content[0], "export"))
		cmd->ft_exec = export_no_args;
	else if (!strcmp(cmd->content[0], "unset"))
		cmd->ft_exec = unset;
	else if (!strcmp(cmd->content[0], "cd"))
		cmd->ft_exec = cd;
	else
		cmd->ft_exec = default_exec;
}

void	check_builtin(cmd_list *cmd)
{
	if (!cmd->content[0])
		return ;
	if (cmd->ft_exec == default_exec)
		cmd->built_in = false;
	else
		cmd->built_in = true;
}

/*
FIND PATH FROM PIPEX

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**allpaths;
	char	*path;
	char	*exec_path;

	i = 0;
	allpaths = ft_split(search_env("PATH", env), ':');
	while (allpaths[i])
	{
		path = ft_strjoin(allpaths[i], "/");
		exec_path = ft_strjoin(path, cmd);
		free(path);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			ft_clean(allpaths);
			return (exec_path);
		}
		free(exec_path);
		i++;
	}
	ft_clean(allpaths);
	return (cmd);
}
*/