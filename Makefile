NAME = minishell

CFILES = 	minishell.c \
			init_shell.c \
			init_modules.c \
			parse_inputs.c \
			parse_utils.c \
			parse_helpers.c \
<<<<<<< HEAD
=======
			open_infile.c \
			open_outfile.c \
			open_heredoc.c \
			child_exec.c \
			child_wait.c \
>>>>>>> e0d1cc17547bbc89b8acdff6b7e8a024b3b254c3
			error_syntax.c \
			error_utils.c \
			free_runtime.c \
			free_utils.c \
			safe_allocs.c \
			safe_strings.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_pwd.c \
			builtin_utils.c \
			utils_path.c \
			utils_envp.c \
			utils_misc.c \
			exec_test.c
##			open_infile.c \
##			open_outfile.c \
##			open_heredoc.c \
##			child_exec.c \
##			child_wait.c

OFILES = ${CFILES:.c=.o}
LIBFT = libft/libft.a

all: ${LIBFT} ${NAME}

${LIBFT}:
	make -C libft

${NAME}: ${OFILES}
	cc ${OFILES} ${LIBFT} -lreadline -g -fsanitize=address -o ${NAME}

${OFILES}: ${CFILES}
	cc -Wall -Wextra -Werror -c ${CFILES} -I minishell.h

clean:
	rm -f ${OFILES}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all