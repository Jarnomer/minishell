# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 15:32:20 by jmertane          #+#    #+#              #
#    Updated: 2024/02/15 11:04:37 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME = minishell

SOURCEDIR := sources
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

LIBFTDIR  := ./libft
LIBFTBIN  := libft.a

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra
LDFLAGS    := -lreadline
CPPFLAGS   := -c -MMD -MP
DEBUGFLAGS := -g -fsanitize=address
MAKEFLAGS  += --no-print-directory -j4

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

LEAKSLOG := leaks.log
SUPPFILE := readline.supp
VLGFLAGS := --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --trace-children=yes \
            --log-file=$(LEAKSLOG) \
            --suppressions=$(SUPPFILE) \
            --verbose \
            --quiet

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

MODULES := lexer \
           parser \
           expand \
           execute \
           builtin \
           signal \
           error \
           debug \
           utils

SOURCES := main \
           env \
           sig \
           sig_utils \
           error \
           err_print \
           lexer \
           lex_token \
           lex_oper \
           lex_word \
           lex_utils \
           parser \
           parse_valid \
           parse_rules \
           parse_shell \
           parse_ast \
           parse_cmd \
           parse_redir \
           parse_utils \
           expand \
           exp_var \
           exp_word \
           exp_wildc \
           exp_wc_utils \
           exp_utils \
           execute \
           exec_ast \
           exec_cmd \
           exec_pipe \
           exec_subs \
           exec_redir \
           exec_path \
           exec_hdoc \
           exec_utils \
           builtin \
           builtin_echo \
           builtin_exit \
           builtin_pwd \
           builtin_cd \
           builtin_env \
           builtin_unset \
           builtin_export \
           builtin_utils \
           debug \
           debug_lexer \
           debug_parser \
           debug_types \
           debug_utils \
           vec \
           vec_utils \
           safe_str \
           try_sysc \
           fd_utils \
           utils

SOURCES := $(addsuffix .c, $(SOURCES))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

SOURCEDIR += $(addprefix $(SOURCEDIR)/, $(MODULES))

INCS := $(addprefix -I, $(HEADERDIR) $(LIBFTDIR)/$(HEADERDIR))

DEPS := $(OBJECTS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) $(LDFLAGS) -o $@
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

$(OBJECTS): $(LIBFTDIR)/$(LIBFTBIN)

libft: $(LIBFTDIR)/$(LIBFTBIN)

$(LIBFTDIR)/$(LIBFTBIN): 
	@make -C $(LIBFTDIR) all

bonus: all

run: all
	$(SCREENCLEAR)
	./$(NAME)

re: fclean
	make all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

nm:
ifneq ($(shell command -v norminette >/dev/null 2>&1 && echo 1 || echo 0), 1)
	@printf "$(R)$(B)Error: norminette: $(Y)command not found$(T)\n"; exit 1
endif
	$(foreach h, $(HEADERDIR), norminette -R CheckDefine $(h))
	$(foreach s, $(SOURCEDIR), norminette -R CheckForbiddenSourceHeader $(s))

leaks: all
	valgrind $(VLGFLAGS) ./$(NAME)
	$(call report_cmd, $(LEAKSLOG))

define report_cmd
	$(SCREENCLEAR)
	sed -n '/ERROR SUMMARY/,$$p' $1 | cut --complement -d' ' -f1
endef

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	@make -C $(LIBFTDIR) fclean
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG), $(LEAKSLOG))

fclean: clean
	$(call delete_cmd, $(NAME))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all libft bonus re nm
.PHONY: run debug leaks
.PHONY: clean fclean

.SILENT:
