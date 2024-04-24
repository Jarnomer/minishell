NAME = minishell

CFILES = 	minishell.c \
			init_shell.c \
			init_modules.c \
			parse_inputs.c \
			parse_argv.c \
			parse_utils.c \
			parse_helpers.c \
			open_infile.c \
			open_outfile.c \
			open_heredoc.c \
			exec_child.c \
			exec_redirect.c \
			exec_command.c \
			wait_child.c \
			error_syntax.c \
			error_utils.c \
			free_runtime.c \
			free_utils.c \
			close_fds.c \
			safe_allocs.c \
			safe_strings.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_pwd.c \
			builtin_exit.c \
			builtin_utils.c \
			utils_envp.c \
			utils_misc.c \
			signal.c

OFILES = ${CFILES:.c=.o}
LIBFT = libft/libft.a
FLAGS = -Wall -Wextra -Werror
READLINE_LIB = ~/.brew/Cellar/readline/8.2.10/lib
READLINE_HEADER = ~/.brew/Cellar/readline/8.2.10/include

all: ${LIBFT} ${NAME}

${LIBFT}:
	make -C libft

${NAME}: ${OFILES}
	cc ${OFILES} ${LIBFT} -L ${READLINE_LIB} -lreadline -I ${READLINE_HEADER} -g -fsanitize=address -o ${NAME}

${OFILES}: ${CFILES}
	cc ${FLAGS} -I ${READLINE_HEADER} -c ${CFILES} -I minishell.h

clean:
	rm -f ${OFILES}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all
