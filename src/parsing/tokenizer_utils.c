/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:56:42 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/07 18:40:52 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// Add a token to the array of tokens
t_token **add_token(t_token **tokens, int *size, t_token *new_token)
{
    t_token **new_tokens;
    int i;

    new_tokens = malloc((*size + 2) * sizeof(t_token *)); // +2 for the new token and NULL terminator
    if (!new_tokens)
        return NULL;
    
    // Copy existing tokens
    i = 0;
    while (i < *size)
    {
        new_tokens[i] = tokens[i];
        i++;
    }

    // Add new token and NULL terminate the array
    new_tokens[*size] = new_token;
    new_tokens[*size + 1] = NULL;

    // Free old tokens array
    if (tokens)
        free(tokens);

    // Update size
    *size += 1;

    return new_tokens;
}

// Add tokens if needed
void add_token_if_needed(char *token, int *token_pos, t_token ***tokens, int *size, t_token_type token_type)
{
    if (*token_pos > 0)
    {
        token[*token_pos] = '\0';  // Null-terminate the token
        t_token *new_token = create_token(token_type, token);  // Create a new token with the provided type
        *tokens = add_token(*tokens, size, new_token);  // Add the token to the array
        *token_pos = 0;  // Reset the position for the next token
    }
}
