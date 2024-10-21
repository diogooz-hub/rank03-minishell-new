/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:32:53 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 08:48:22 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Expand tilde (~) using the HOME environment variable from program->env
void	expand_tilde(t_token **token, t_program *program)
{
    t_env_var *temp;

	if (ft_strcmp((*token)->content, "~") == 0)
        free((*token)->content);
	temp = program->env_list;
    while (temp)
    {
        if (ft_strcmp("HOME", temp->name) == 0)
		{
			(*token)->content = ft_strdup(temp->value);
			return ;
		}
		temp = temp->next;
	}
	(*token)->content = ft_strdup("");
}

// Expand environment variables using program->env
char *expand_env_var(char *str, t_program *program)
{
    t_env_var *temp;

	temp = program->env_list;
    while (temp)
    {
        if (ft_strcmp(str + 1, temp->name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL; // Return NULL if the environment variable is not found
}

void	expand_variable(t_token **token, t_program *program)
{
	char	*expanded_value;

    if (ft_strcmp((*token)->content, "$?") == 0)
    {
    	free((*token)->content);
    	(*token)->content = ft_itoa(program->exit_status);
    }
    else if ((*token)->content[0] == '$')
    {
        expanded_value = expand_env_var((*token)->content, program);
		free((*token)->content);
        if (expanded_value)
            (*token)->content = ft_strdup(expanded_value); // Make a copy of the expanded value
		else
		{
			(*token)->content = ft_strdup("");  // Set to empty string if the variable is not found
			(*token)->type = STRING;  // Change the type to STRING
		}
    }
}

// Expand tokens that include environment variables or special symbols
void expand_tokens(t_token **tokens, t_program *program)
{
    int i;

	i = 0;
	while (tokens[i])
    {
        if (tokens[i]->type == VARIABLE || tokens[i]->type == TILDE)
        {
			if (tokens[i]->type == TILDE)
				expand_tilde(&tokens[i], program);
			else
				expand_variable(&tokens[i], program);
        }
        i++;
    }
}
