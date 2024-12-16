# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/05/09 17:26:20 by jmertane         ###   ########.fr        #
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

TESTCASE  := ./$(NAME)

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra -lreadline
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

MODULES := builtins \
           parser \
           exec \
           free \
           open \
           init \
           error \
           utils

SOURCES = main \
          signals \
          init_shell \
          init_modules \
          parse_mods \
          parse_input \
          parse_envps \
          parse_expand \
          parse_files \
          parser_utils \
          parser_helpers \
          open_infile \
          open_outfile \
          open_heredoc \
          exec_child \
          exec_redirect \
          exec_command \
          wait_child \
          error_syntax \
          error_utils \
          free_runtime \
          free_utils \
          close_fds \
          safe_allocs \
          safe_strings \
          builtin_cd \
          builtin_echo \
          builtin_env \
          builtin_export \
          builtin_unset \
          builtin_pwd \
          builtin_exit \
          builtin_utils \
          envp_utils \
          envp_print

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
	$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) -o $@
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

$(OBJECTS): $(LIBFTDIR)/$(LIBFTBIN)

libft: $(LIBFTDIR)/$(LIBFTBIN)

$(LIBFTDIR)/$(LIBFTBIN): 
	@make -C $(LIBFTDIR) all

run: all
	$(SCREENCLEAR)
	$(TESTCASE)

re: fclean
	make all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

nm:
	$(foreach d, $(HEADERDIR), $(foreach h, $(wildcard $(d)/*), \
		norminette -R CheckDefine $(h);))
	$(foreach d, $(SOURCEDIR), $(foreach s, $(wildcard $(d)/*), \
		norminette -R CheckForbiddenSourceHeader $(s);))

leaks: all
	valgrind $(VLGFLAGS) $(TESTCASE)

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

.PHONY: all libft re nm
.PHONY: debug leaks run
.PHONY: clean fclean

.SILENT:
