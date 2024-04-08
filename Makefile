NAME = minishell

CFILES = 	minishell.c \
			init_shell.c \
			init_modules.c \
			parse_inputs.c \
			parse_utils.c \
			parse_helpers.c \
			open_infile.c \
			open_outfile.c \
			open_heredoc.c \
			child_exec.c \
			error_syntax.c \
			error_utils.c \
			free_runtime.c \
			free_utils.c \
			safe_allocs.c \
			safe_strings.c \
			utils_path.c \
			utils_misc.c \
			misc_utils.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_pwd.c \
			builtin_utils.c \
			envp_utils.c
##			child_exec.c
##			child_wait.c
##			parse_files.c

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