/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:33:20 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 08:42:45 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	only_tab(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '\t' && input[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	validate_input_quotes(t_program *program)
{
	int		i;
	int		count_quotes;
	int		count_dquotes;

	i = 0;
	count_quotes = 0;
	count_dquotes = 0;
	while (program->input[i])
	{
		if (program->input[i] == '\'')
			count_quotes++;
		if (program->input[i] == '"')
			count_dquotes++;
		i++;
	}
	if (count_quotes % 2 != 0 || count_dquotes % 2 != 0)
		return (false);
	return (true);
}

bool	validate_input(t_program *program)
{
	if (!program->input || !program->input[0])
	{
		printf("focus mfker, you have an empty input\n");
		program->exit_status = 2;
		return (false);
	}
	if (only_tab(program->input))
		return (false);
	if (!validate_input_quotes(program))
	{
		printf("focus mfker, you have an unclosed quote\n");
		program->exit_status = 2;
		return (false);
	}
	return (true);
}
