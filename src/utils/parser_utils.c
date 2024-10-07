/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:33:20 by dpaco             #+#    #+#             */
/*   Updated: 2024/09/20 09:21:33 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	validate_input(t_program *program)
{
	int		i;
	int		count_quotes;
	int		count_dquotes;
	char	*input;
	bool	ret;

	ret = true;
	i = 0;
	count_quotes = 0;
	count_dquotes = 0;
	if (!program->input || !program->input[0])
	{
		printf("focus mfker, you have an empty input\n");
		program->exit_status = 2;
		return (false);
	}
	input = program->input;
	while (program->input[i])
	{
		if (input[i] == '\'')
			count_quotes++;
		if (input[i] == '"')
			count_dquotes++;
		if ((input[i] == '>' || input[i] == '<') && (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t'))
			ret = false;
		if ((input[i] == '|' || input[i] == '&') && input[i+1] == input[i])
		{
			i++;
			if (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t')
				ret = false;
		}
		else if (input[i] == '|' && (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t'))
			ret = false;
		i++;
	}
	if (!ret)
	{
		printf("focus mfker, you have a syntax error\n");
		program->exit_status = 2;
		return (ret);
	}
	if (count_quotes % 2 != 0 || count_dquotes % 2 != 0)
	{
		printf("focus mfker, you have an unclosed quote\n");
		program->exit_status = 2;
		return (false);
	}
	return (ret);
}