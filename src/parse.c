/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:10:03 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/08 23:06:29 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

cmd_list	*new_cmd_node(t_env_var *env, t_program *program)
{
	cmd_list	*new_node;

	new_node = (cmd_list *)malloc(sizeof(cmd_list));
	if (!new_node)
		return (NULL);
	new_node->prog = program;
	new_node->env = env;
	new_node->content = NULL;
	new_node->path = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->built_in = false;
	new_node->on_parent = false;
	new_node->ft_exec = NULL;
	new_node->fd_master[0] = STDIN_FILENO;
	new_node->fd_master[1] = STDOUT_FILENO;
	new_node->fd[0] = -1;
	new_node->fd[1] = -1;
	return (new_node);
}

void add_token_to_cmd(cmd_list *cmd, char *token_value)
{
	char	**new_content;
	int		i;
	int		j;

	i = 0;
	while (cmd->content && cmd->content[i])
		i++;
	new_content = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_content)
	{
		perror("malloc error");
		exit(1);
	}
	j = 0;
	while (j < i)
	{
		new_content[j] = cmd->content[j];
		j++;
	}
	new_content[i] = strdup(token_value);
	new_content[i + 1] = NULL;
	free(cmd->content);
	cmd->content = new_content;
}

void	handle_pipe_token(cmd_list **current_node, cmd_list **last_node, t_program *program)
{
	*current_node = new_cmd_node(program->env, program);
	if (*last_node)
	{
		(*last_node)->next = *current_node;
		(*current_node)->prev = *last_node;
	}
	else
		program->cmds = *current_node;
	*last_node = *current_node;
}

void	handle_cmd_token(cmd_list **current_node, t_token *token, cmd_list **last_node, t_program *program)
{
	if (!*current_node)
	{
		*current_node = new_cmd_node(program->env, program);
		program->cmds = *current_node;
		*last_node = *current_node;
	}
	add_token_to_cmd(*current_node, token->content);
}

void parse_tokens_to_cmd_list(t_token **tokens, t_program *program)
{
	cmd_list	*current_node;
	cmd_list	*last_node;
	int			i;

	current_node = NULL;
	last_node = NULL;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == PIPE)
			handle_pipe_token(&current_node, &last_node, program);
		else if (tokens[i]->type == REDIRECTION)
			set_file_descriptors(tokens, &i, current_node);
		else
			handle_cmd_token(&current_node, tokens[i], &last_node, program);
		i++;
	}
}

void parse(t_program *program)
{
    t_token 	**tokens;

	//printf("Parsing input: %s\n", program->input);
    if (!validate_input(program))
        return;
	//printf("Input is valid\n");
    tokens = tokenize(program->input);
	print_tokens1(tokens);
	expand_tokens(tokens, program);
	//printf("Expanded tokens\n");
	//print_tokens1(tokens);
    parse_tokens_to_cmd_list(tokens, program);
	//print_cmd_list(program);
    //free_tokens(tokens);
}
