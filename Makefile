NAME = minishell

CFILES = 	minishell.c \
			init_shell.c \
			init_environ.c \
			init_modules.c \
			utils_parser.c \
			free_runtime.c \
			free_destruct.c \
			free_utils.c \
			safe_utils.c

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
