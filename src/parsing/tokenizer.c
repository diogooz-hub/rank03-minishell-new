/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:31:17 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/21 19:30:26 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle operators
void handle_operator(char *input, int *i, char **token, t_token ***tokens)
{
	t_token_type token_type;

	if (input[*i] == '|')
		token_type = PIPE;
	else
		token_type = REDIRECTION;
    update_token(token, input[*i]);
    if ((input[*i] == '<' && input[*i + 1] == '<') ||
        (input[*i] == '>' && input[*i + 1] == '>'))
    {
		(*i)++;
        update_token(token, input[*i]);
    }
	add_token_if_needed(token, tokens, token_type);
}


void handle_variable(char *input, int *i, char **token, t_token ***tokens, int in_quotes, char quote_char)
{
    if (in_quotes && quote_char == '\'')
		add_token_if_needed(token, tokens, STRING);
	update_token(token, input[*i]);
    (*i)++;  // Move to the next character
    if (input[*i] == '?')
    {
		update_token(token, input[*i]);
        (*i)++;
    }
    else if (ft_isalnum(input[*i]) || input[*i] == '_')
    {
        while (ft_isalnum(input[*i]) || input[*i] == '_')
        {
            update_token(token, input[*i]);
			(*i)++;
        }
    }
    else
    {
        (*i)--;  // Step back so that the next character can be handled
		*token[ft_strlen(*token) - 1] = '\0';  // Null-terminate the variable token
		return;
    }
	add_token_if_needed(token, tokens, VARIABLE);
}


void handle_quoted_string(char *input, int *i, char **token, int *in_quotes, char *quote_char, t_token ***tokens)
{
    *in_quotes = 1;
    *quote_char = input[*i];  // Store the type of quote (' or ")
    (*i)++;  // Move past the opening quote
    while (input[*i] != '\0')
    {
        if (input[*i] == *quote_char)
        {
            *in_quotes = 0;
            *quote_char = '\0';
            (*i)++;  // Move past the closing quote
            return;
        }
        // If we encounter a variable inside double quotes, handle it
        if (input[*i] == '$' && *quote_char == '"')
        {
            // Only add the string token if there's actual content before the variable
			if (*token[0] != '\0')
				add_token_if_needed(token, tokens, STRING);
            // Call handle_variable to process the variable
            handle_variable(input, i, token, tokens, *in_quotes, *quote_char);
            continue;  // After handling the variable, continue processing the string
        }
		update_token(token, input[*i]);
        (*i)++;
    }
    // Add the remaining string token if necessary
	if (*token[0] != '\0')
		add_token_if_needed(token, tokens, STRING);
    // Handle missing closing quote error
    if (*in_quotes)
    {
        printf("Error: missing closing quote.\n");
        exit(1);
    }
}

void handle_tilde(char **token, t_token ***tokens)
{
	update_token(token, '~');
	add_token_if_needed(token, tokens, TILDE);
}

// Main tokenizer function
t_token **tokenize(char *input)
{
    t_token **tokens;
    char *token;
    int i;
    int in_quotes;  // Track whether we are inside quotes
    char quote_char;  // Track which type of quote (' or ")

	tokens = NULL;
	token = malloc(1);
	token[0] = '\0';
	in_quotes = 0;
	quote_char = '\0';
	i = 0;
    while (input[i] != '\0')
    {
        if (is_whitespace(input[i]) && !in_quotes)
			add_token_if_needed(&token, &tokens, STRING);
        else if (input[i] == '\'' || input[i] == '"')
        {
			add_token_if_needed(&token, &tokens, STRING);
			handle_quoted_string(input, &i, &token, &in_quotes, &quote_char, &tokens);
        }
        else if (input[i] == '$' && (!in_quotes || quote_char == '"'))
        {
            add_token_if_needed(&token, &tokens, STRING);
			handle_variable(input, &i, &token, &tokens, in_quotes, quote_char);
        }
        else if (is_operator(input[i]) && !in_quotes)
        {
            add_token_if_needed(&token, &tokens, STRING);
			handle_operator(input, &i, &token, &tokens);
        }
        else if (input[i] == '~' && !in_quotes)
        {
            add_token_if_needed(&token, &tokens, STRING);
			handle_tilde(&token, &tokens);
        }
        else
			update_token(&token, input[i]);
        i++;  // Move to the next character
    }
    add_token_if_needed(&token, &tokens, STRING);
	if (token)
		free(token);
	return tokens;
}
