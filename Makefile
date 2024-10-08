CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lreadline
NAME = minishell
SRCS = src/minishell.c src/execute.c src/parse.c src/debugers.c\
		src/commands/export.c src/commands/unset.c src/commands/cd.c src/commands/clear.c src/commands/echo.c src/commands/env.c src/commands/exit.c src/commands/pwd.c \
		src/execution/default_exec.c src/execution/execute_errors.c src/execution/fd_redirection.c \
		src/parsing/tokenizer.c src/parsing/tokenizer_utils.c src/parsing/is_single_cmd.c src/parsing/parsing_redirections.c src/parsing/expand_tokens.c\
		src/utils/init_env.c src/parsing/is_quotes.c src/utils/executer_utils.c src/utils/utils.c src/utils/exit_status.c src/utils/parser_utils.c src/utils/clean_program.c

LIBFT = libraries/Libft/libft.a

OBJS = $(SRCS:.c=.o)

RM = rm -f

# Define colors
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDLIBS)
	@printf "${GREEN}\n--------------------------\n-MINISHELL COMPILED MFKRS-\n--------------------------\n${NC}"
	@printf "\nRun with ./${NAME} and test with some care\n\n"

$(LIBFT):
	@make -s -C libraries/Libft
	@make bonus -s -C libraries/Libft

clean:
	@$(RM) $(OBJS)
	@make clean -s -C libraries/Libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C libraries/Libft

re: fclean $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re program clean_output precompile postcompile
