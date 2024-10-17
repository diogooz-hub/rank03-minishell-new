/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:09:38 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/17 08:37:38 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char *token_type_to_string(t_token_type type) {
    switch (type) {
        case OPERATOR: return "OPERATOR";
        case STRING: return "STRING";
        case REDIRECTION: return "REDIRECTION";
        case PIPE: return "PIPE";
        case VARIABLE: return "VARIABLE";
		case TILDE: return "TILDE";
        default: return "UNKNOWN";
    }
}


void print_tokens1(t_token **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token Type: %s, Token Content: '%s'\n", token_type_to_string(tokens[i]->type), tokens[i]->content);
        i++;
    }
}

void print_cmd_list(t_program *program)
{
    cmd_list *current_cmd = program->cmds;
    int cmd_index = 1;

    while (current_cmd)
    {
        printf("Command %d:\n", cmd_index);

        // Print the command content
        if (current_cmd->content)
        {
            int i = 0;
            while (current_cmd->content[i])
            {
                printf("  Arg[%d]: %s\n", i, current_cmd->content[i]);
                i++;
            }
        }

        // Print the file descriptors for input and output
        printf("  Input FD: %d\n", current_cmd->fd_master[0]);
        printf("  Output FD: %d\n", current_cmd->fd_master[1]);

        current_cmd = current_cmd->next;
        cmd_index++;
    }
}