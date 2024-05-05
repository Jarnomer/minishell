# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/05/05 20:48:52 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	minishell
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps
LIBFTDIR	:=	libft
LIBFTBIN	:=	$(LIBFTDIR)/libft.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g #-fsanitize=address
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPENDDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

RL_FLG		:=	-lreadline
RL_LIB		:=	-L ~/.brew/Cellar/readline/8.2.10/lib
RL_INC		:=	-I ~/.brew/Cellar/readline/8.2.10/include

MODULES		:=	main \
				buildins \
				parser \
				exec \
				free \
				open \
				init \
				error \
				utils

SOURCES 	= 	minishell.c \
				init_shell.c \
				init_modules.c \
				parse_mods.c \
				parse_input.c \
				parse_envps.c \
				parse_files.c \
				parser_utils.c \
				parser_helpers.c \
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
				envp_utils.c \
				envp_print.c \
				signals.c

SOURCEDIR	:=	$(addprefix $(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	+=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))

F			=	=====================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

vpath %.c $(SOURCEDIR)

define cc_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(RL_INC) -c $$< -o $$@ 2> $(ERRTXT); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $$<$ \n    $(C)⮑\t$(G)$(B)$$@$(T) \t\n"; \
	fi
endef

all: $(LIBFTBIN) $(NAME)

$(LIBFTBIN):
	@make --quiet -C $(LIBFTDIR) all
	@make title

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(RL_INC) $(RL_FLG) $(RL_LIB) $^ $(LIBFTBIN) -o $@
	@make finish

debug: CFLAGS += $(DEBUGFLAGS)
debug: all

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRTXT)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

title:
	@$(SCREENCLR) && printf "\n"
	@printf "$(C)╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦$(T)\n"
	@printf "$(C)║║║║║║║║╚═╗╠═╣║╣ ║  ║   by vkinaret$(T)\n"
	@printf "$(C)╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝  & jmertane$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"

finish:
	@printf "\n$(G)$(B)$(F)$(T)\n"
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗        $(V)$(B)$(NAME)$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call cc_cmd, $(build))))

.PHONY: all debug clean fclean re
