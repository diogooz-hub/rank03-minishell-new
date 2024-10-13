/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:06:51 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/13 18:10:47 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_error(t_program *program, char *error)
{
	if (!strcmp(error, "syntax"))
	{
		printf("minishell: syntax error\n");
		program->exit_status = 2;
	}
	else if (!strcmp(error, "pipe"))
	{
		printf("minishell: pipe error\n");
		program->exit_status = 2;
	}
	else if (!strcmp(error, "redirection"))
	{
		printf("minishell: redirection error\n");
		program->exit_status = 2;
	}
	else if (!strcmp(error, "variable"))
	{
		printf("minishell: variable error\n");
		program->exit_status = 2;
	}
	else if (!strcmp(error, "tilde"))
	{
		printf("minishell: tilde error\n");
		program->exit_status = 2;
	}
	else if (!strcmp(error, "env"))
	{
		printf("minishell: env error\n");
		program->exit_status = 2;
	}
}