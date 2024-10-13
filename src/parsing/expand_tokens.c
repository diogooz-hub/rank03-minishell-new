/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:32:53 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/13 18:11:32 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Expand tilde (~) using the HOME environment variable from program->env
char *expand_tilde(t_program *program)
{
    t_env_var *temp = program->env;

    while (temp)
    {
        if (ft_strcmp("HOME", temp->name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL; // Return NULL if HOME is not found
}

// Expand environment variables using program->env
char *expand_env_var(char *str, t_program *program)
{
    t_env_var *temp = program->env;

    // The variable name starts after the '$' symbol
    while (temp)
    {
        if (ft_strcmp(str + 1, temp->name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL; // Return NULL if the environment variable is not found
}

// Expand tokens that include environment variables or special symbols
void expand_tokens(t_token **tokens, t_program *program)
{
    int i = 0;

    while (tokens[i])
    {
        // Check for VARIABLE type tokens
        if (tokens[i]->type == VARIABLE || tokens[i]->type == TILDE)
        {
            // Handle tilde expansion
            if (ft_strcmp(tokens[i]->content, "~") == 0)
            {
                free(tokens[i]->content);
                tokens[i]->content = ft_strdup(expand_tilde(program));
            }
            // Handle $? to expand the exit status
            else if (ft_strcmp(tokens[i]->content, "$?") == 0)
            {
                free(tokens[i]->content);
                tokens[i]->content = ft_itoa(program->exit_status);
            }
            // Handle regular environment variable expansion (e.g., $USER)
            else if (tokens[i]->content[0] == '$')
            {
                char *expanded_value = expand_env_var(tokens[i]->content, program);
                if (expanded_value)
                {
                    free(tokens[i]->content);
                    tokens[i]->content = ft_strdup(expanded_value); // Make a copy of the expanded value
                }
				else
				{
					free(tokens[i]->content);
					tokens[i]->content = ft_strdup("");  // Set to empty string if the variable is not found
					tokens[i]->type = STRING;  // Change the type to STRING
				}
            }
        }
        i++;
    }
}
