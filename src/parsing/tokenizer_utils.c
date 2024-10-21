/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:56:42 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 08:46:07 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_token(char **current_token, char c)
{
	char	*new_token;
	int		i;

	new_token = malloc(ft_strlen(*current_token) + 2);
	if (!new_token)
		return ;
	i = 0;
	while ((*current_token)[i])
	{
		new_token[i] = (*current_token)[i];
		i++;
	}
	new_token[i] = c;
	new_token[i + 1] = '\0';
	free(*current_token);
	*current_token = new_token;
}

// Free the tokens array
void free_tokens(t_token **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        free(tokens[i]->content);
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// Check if the character is an operator
int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&');
}

// Check if the character is whitespace
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Create a new token
t_token *create_token(t_token_type type, const char *content)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->content = ft_strdup(content);
    return new_token;
}
int get_token_array_size(t_token **tokens)
{
    int size = 0;

    if (!tokens)
        return 0;
    while (tokens[size] != NULL)
        size++;
    return size;
}

// Add a token to the array of tokens
t_token **add_token(t_token **tokens, t_token *new_token)
{
    t_token **new_tokens;
    int i;
    int size;

    size = get_token_array_size(tokens);
    new_tokens = malloc((size + 2) * sizeof(t_token *)); // +2 for the new token and NULL terminator
    if (!new_tokens)
        return NULL;
    i = 0;
    while (i < size)
    {
        new_tokens[i] = tokens[i];
        i++;
    }
    new_tokens[size] = new_token;
    new_tokens[size + 1] = NULL;
    if (tokens)
        free(tokens);
    return new_tokens;
}

void	add_token_if_needed(char **token, t_token ***tokens, t_token_type token_type)
{
    if (*token[0] != '\0')
    {
        t_token *new_token = create_token(token_type, *token);  // Create a new token with the provided type
        *tokens = add_token(*tokens, new_token);  // Add the token to the array
		free(*token);
		*token = malloc(1);
		*token[0] = '\0';
    }
}
