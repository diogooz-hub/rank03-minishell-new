/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:31:17 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/16 20:53:27 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle operators
void handle_operator(char *input, int *i, char *token, int *token_pos, t_token ***tokens)
{
	t_token_type token_type;

	if (input[*i] == '|')
		token_type = PIPE;
	else
		token_type = REDIRECTION;
    token[(*token_pos)++] = input[*i];  // Add operator character to token
    // Handle special cases for multi-character operators (e.g. "<<", ">>")
    if ((input[*i] == '<' && input[*i + 1] == '<') ||
        (input[*i] == '>' && input[*i + 1] == '>'))
    {
        token[(*token_pos)++] = input[++(*i)];  // Add the second character of the operator
    }
	/*
    token[*token_pos] = '\0';  // Null-terminate the token
    // Directly create the OPERATOR token, no need for get_token_type
    t_token *new_token = create_token(OPERATOR, token);  // Create an OPERATOR token
    *tokens = add_token(*tokens, size, new_token);  // Add the token to the token array
    *token_pos = 0;  // Reset token position
	*/
	add_token_if_needed(token, token_pos, tokens, token_type);
}


void handle_variable(char *input, int *i, char *token, int *token_pos, t_token ***tokens, int in_quotes, char quote_char)
{
    // If inside single quotes, treat the variable as part of the string
    if (in_quotes && quote_char == '\'')
    {
		/*
        token[*token_pos] = '\0';  // Terminate the preceding string
        t_token *new_token = create_token(STRING, token);  // Create a string token
        *tokens = add_token(*tokens, size, new_token);  // Add the string token
        *token_pos = 0;  // Reset token position
		*/
		add_token_if_needed(token, token_pos, tokens, STRING);
    }

    // Handle variables normally (outside quotes or inside double quotes)
    token[(*token_pos)++] = input[*i]; // Add the '$'
    (*i)++;  // Move to the next character

    // Handle special case: $?
    if (input[*i] == '?')
    {
        token[(*token_pos)++] = input[*i];
        (*i)++;
    }
    // Handle valid variable names (alphanumeric or underscores)
    else if (ft_isalnum(input[*i]) || input[*i] == '_')
    {
        while (ft_isalnum(input[*i]) || input[*i] == '_')
        {
            token[(*token_pos)++] = input[*i];
            (*i)++;
        }
    }
    else
    {
        // Invalid variable, treat as a standalone '$'
        (*i)--;  // Step back so that the next character can be handled
		token[(*token_pos) - 1] = '\0';  // Null-terminate the variable token
		*token_pos = 0;  // Reset token position
		return;
    }

	/*
    token[*token_pos] = '\0';  // Terminate the variable token
    t_token *new_token = create_token(VARIABLE, token);  // Create a variable token
    *tokens = add_token(*tokens, size, new_token);  // Add the variable token
    *token_pos = 0;  // Reset token position
	*/
	add_token_if_needed(token, token_pos, tokens, VARIABLE);
}

// Handle quoted strings and create the token directly within this function
void handle_quoted_string(char *input, int *i, char *token, int *token_pos, int *in_quotes, char *quote_char, t_token ***tokens)
{
    *in_quotes = 1;
    *quote_char = input[*i];  // Store the type of quote (' or ")
    (*i)++;  // Move past the opening quote

    // If inside single quotes, treat everything as string
    while (input[*i] != '\0')
    {
        // If we encounter the closing quote, stop processing the string
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
            if (*token_pos > 0)
            {
				/*
                token[*token_pos] = '\0';
                t_token *new_token = create_token(STRING, token);
                *tokens = add_token(*tokens, size, new_token);
                *token_pos = 0;
				*/
				add_token_if_needed(token, token_pos, tokens, STRING);
            }

            // Call handle_variable to process the variable
            handle_variable(input, i, token, token_pos, tokens, *in_quotes, *quote_char);
            continue;  // After handling the variable, continue processing the string
        }

        // Regular characters inside the quotes
        token[(*token_pos)++] = input[*i];
        (*i)++;
    }

    // Add the remaining string token if necessary
    if (*token_pos > 0)
    {
		/*
        token[*token_pos] = '\0';
        t_token *new_token = create_token(STRING, token);
        *tokens = add_token(*tokens, size, new_token);
        *token_pos = 0;
		*/
		add_token_if_needed(token, token_pos, tokens, STRING);
    }

    // Handle missing closing quote error
    if (*in_quotes)
    {
        printf("Error: missing closing quote.\n");
        exit(1);
    }
}

void handle_tilde(char *token, int *token_pos, t_token ***tokens)
{
	token[(*token_pos)++] = '~';  // Add the tilde character
	add_token_if_needed(token, token_pos, tokens, TILDE);
}

// Main tokenizer function
t_token **tokenize(char *input)
{
    t_token **tokens;
    char *token;
    int token_pos = 0;
    int i;
    int in_quotes;  // Track whether we are inside quotes
    char quote_char;  // Track which type of quote (' or ")

	tokens == NULL;
	token = malloc(1);
	token[0] = '\0';
	in_quotes = 0;
	quote_char = '\0';
	i = 0;
    while (input[i] != '\0')
    {
		token = update_token(token, input[i]);
        if (is_whitespace(input[i]) && !in_quotes)
        {
            // Handle token end when not inside quotes
            add_token_if_needed(token, &token_pos, &tokens, STRING);
        }
        else if (input[i] == '\'' || input[i] == '"')
        {
            // Handle quoted strings
            add_token_if_needed(token, &token_pos, &tokens, STRING);  // Add any previous token before handling quotes
            handle_quoted_string(input, &i, token, &token_pos, &in_quotes, &quote_char, &tokens);
        }
        else if (input[i] == '$' && (!in_quotes || quote_char == '"'))
        {
            // Handle variables
            add_token_if_needed(token, &token_pos, &tokens, STRING);  // Add any previous string token
            handle_variable(input, &i, token, &token_pos, &tokens, in_quotes, quote_char);
        }
        else if (is_operator(input[i]) && !in_quotes)
        {
            // Handle operators
            add_token_if_needed(token, &token_pos, &tokens, STRING);  // Add any previous token
            handle_operator(input, &i, token, &token_pos, &tokens);
        }
        else if (input[i] == '~' && !in_quotes)
        {
            // Handle tilde separately
            add_token_if_needed(token, &token_pos, &tokens, TILDE);
			handle_tilde(token, &token_pos, &tokens);
        }
        else
        {
            // Handle regular characters
            token[token_pos++] = input[i];
        }
        i++;  // Move to the next character
    }

    // Add any remaining token
    add_token_if_needed(token, &token_pos, &tokens, STRING);

	if (token)
		free(token);
	return tokens;
}
