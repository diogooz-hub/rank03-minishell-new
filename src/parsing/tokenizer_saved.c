/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_saved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:55:51 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/07 17:58:37 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// Determine the token type
t_token_type get_token_type(const char *token, int in_quotes, char quote_char)
{
    if ((in_quotes && quote_char == '\'') ) {
        // Inside single quotes, treat everything as STRING
        return STRING;
    }

	//if (token[0] == '"' || token[0] == '\'')
    //    return STRING;
    else if (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0)
        return OPERATOR;
    else if (ft_strcmp(token, "|") == 0)
        return PIPE;
    else if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
        return REDIRECTION;
    else if (token[0] == '$' && quote_char != '\'')
        return VARIABLE;
    else
        return STRING;
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
void add_token_if_needed(char *token, int *token_pos, t_token ***tokens, int *size, int in_quotes, char quote_char)
{
    if (*token_pos > 0)
    {
        token[*token_pos] = '\0';
        
        // Determine the token type, passing in_quotes and quote_char
        t_token_type token_type = get_token_type(token, in_quotes, quote_char);
        t_token *new_token = create_token(token_type, token);
        
        *tokens = add_token(*tokens, size, new_token);
        *token_pos = 0;
    }
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

// Check if the character is whitespace
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Handle operators
void handle_operator(char *input, int *i, char *token, int *token_pos, t_token ***tokens, int *size)
{
    if (*token_pos > 0)
    {
        add_token_if_needed(token, token_pos, tokens, size, 0, '\0');
    }
    
    token[(*token_pos)++] = input[*i];
    if ((input[*i] == '<' && input[*i + 1] == '<') ||
        (input[*i] == '>' && input[*i + 1] == '>') ||
        (input[*i] == '&' && input[*i + 1] == '&') ||
        (input[*i] == '|' && input[*i + 1] == '|'))
    {
        token[(*token_pos)++] = input[++(*i)];
    }
    
    token[*token_pos] = '\0';
    t_token *new_token = create_token(get_token_type(token, 0, '\0'), token);
    *tokens = add_token(*tokens, size, new_token);
    *token_pos = 0;
}

// Handle quoted strings
int handle_quoted_string(char *input, int *i, char *token, int *token_pos, int *in_quotes, char *quote_char)
{
    // Start quote
    int ret;

	ret = 0;
	*in_quotes = 1;
    *quote_char = input[*i];  // Store the type of quote (' or ")
    (*i)++;  // Move past the opening quote

    while (input[*i] != '\0')
    {
        if (input[*i] == *quote_char)  // Check if it's the closing quote
			{
				if (*quote_char == '"')
					ret = 1;
				*in_quotes = 0;  // End quote
				*quote_char = '\0';  // Reset quote char
				return ret;  // Exit the function, we've found the closing quote
			}
        token[(*token_pos)++] = input[*i];  // Add character inside the quotes to the token
        (*i)++;  // Move to the next character
    }
    // If we reach the end of input without finding the closing quote, it's an error
    printf("Error: missing closing quote.\n");
    exit(1);  // Exit with an error status
}


// Check if the character is an operator
int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&');
}

// Handle variables
void handle_variable(char *input, int *i, char *token, int *token_pos, t_token ***tokens, int *size, int in_quotes, char quote_char)
{
    // Add any preceding string part before $
    if (*token_pos > 0 && in_quotes && quote_char == '\'')
    {
        token[*token_pos] = '\0';
        t_token *new_token = create_token(STRING, token);
        *tokens = add_token(*tokens, size, new_token);
        *token_pos = 0;
    }

    // Special case: $"123$USER" should separate into a string and a variable
    if (input[*i] == '$' && input[*i + 1] == '"')
    {
        (*i)++; // Skip the $ and quote
        (*i)++; // Skip the opening quote
        
        // Read until another $ or closing quote
        while (input[*i] != '\0' && input[*i] != '$' && input[*i] != '"')
        {
            token[(*token_pos)++] = input[*i];
            (*i)++;
        }

        // Add the string part
        token[*token_pos] = '\0';
        t_token *new_token = create_token(STRING, token);
        *tokens = add_token(*tokens, size, new_token);
        *token_pos = 0;

        // Now handle the $USER part (variable)
        if (input[*i] == '$')
        {
            token[(*token_pos)++] = input[(*i)++]; // Add '$'
            while (ft_isalnum(input[*i]) || input[*i] == '_')
            {
                token[(*token_pos)++] = input[*i];
                (*i)++;
            }
            token[*token_pos] = '\0';
            new_token = create_token(VARIABLE, token);  // Variable token
            *tokens = add_token(*tokens, size, new_token);
            *token_pos = 0;
        }

        // Skip the closing quote
        if (input[*i] == '"')
            (*i)++;

        return;
    }

    // Handle standard variables outside of $""
    token[(*token_pos)++] = input[*i]; // Add '$'
    (*i)++; // Move to the next character

    // Handle special case: $?
    if (input[*i] == '?')
    {
        token[(*token_pos)++] = input[(*i)];
        (*i)++;
    }
    // Handle valid variable names
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
        // Invalid variable, treat '$' as a standalone string
        (*i)--; // Step back so that we don't skip the character after '$'
    }

    token[*token_pos] = '\0'; // Terminate the token
    t_token *new_token = create_token(VARIABLE, token);
    *tokens = add_token(*tokens, size, new_token);
    *token_pos = 0;
}

// Main tokenizer function
t_token **tokenize(char *input)
{
    t_token **tokens = NULL;
    char token[1000];
    int token_pos = 0;
    int i = 0;
    int size = 0;
    int in_quotes = 0;  // Track whether we are inside quotes
    char quote_char = '\0';  // Track which type of quote (' or ")

    while (input[i] != '\0')
    {
        if (is_whitespace(input[i]) && !in_quotes)
        {
            // Handle token end when not inside quotes
            add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
        }
        else if (input[i] == '\'' || input[i] == '"')
        {
			add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
            // Handle quoted strings
            if (!handle_quoted_string(input, &i, token, &token_pos, &in_quotes, &quote_char))
				add_token_if_needed(token, &token_pos, &tokens, &size, 0, '\'');
			else
				add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
        }
        else if (input[i] == '$' && (!in_quotes || quote_char == '"'))
        {
            // Handle variables when outside quotes or inside double quotes
            add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
            handle_variable(input, &i, token, &token_pos, &tokens, &size, in_quotes, quote_char);
        }
        else if (is_operator(input[i]) && !in_quotes)
        {
            // Handle operators
            add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
            handle_operator(input, &i, token, &token_pos, &tokens, &size);
        }
		else if (input[i] == '~' && !in_quotes)
		{
			// Ensure we add any previous token first
    		add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
			// Create a new token for the tilde
			t_token *new_token = create_token(TILDE, "~");
			tokens = add_token(tokens, &size, new_token);
		}
        else
            token[token_pos++] = input[i];
        i++;  // Move to the next character
    }
    // Add any remaining token
    add_token_if_needed(token, &token_pos, &tokens, &size, in_quotes, quote_char);
    return tokens;
}