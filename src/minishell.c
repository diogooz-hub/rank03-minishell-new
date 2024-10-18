/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:33:57 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/18 18:10:40 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_program(t_program *program, char **envp)
{
	program->exit_status = 0;
	program->cmds = NULL;
	program->input = NULL;
	//program->init_env = envp;
	program->env_list = NULL;
	program->env_array = NULL;
	init_env(program, envp);
}
void ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
    //rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void ctrl_slash(int signum)
{
	(void)signum;
}

int	main(int ac, char **av, char **envp)
{
	t_program	program;

	(void)av;
	init_program(&program, envp);
	if (ac != 1)
	{
		printf("This program must have no arguments!\n");
		exit(-1);
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		program.input = readline("homemade minishell: ");
		if (!program.input)
		{
			free_program(&program);
			printf("exit");
			exit(-1);
		}
		add_history(program.input);
		parse(&program);
		if (program.cmds && program.cmds->content[0])
			executer(program.cmds);
		//printf("exit_status: %d\n", program.exit_status);
		free_program_continue(&program);
	}
	return (0);
}
