# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:42:13 by jmertane          #+#    #+#              #
#    Updated: 2024/05/05 15:50:29 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	minishell
OBJSDIR		:=	objs
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps
ERRORTXT	:=	error.txt
LIBFTDIR	:=	libft
LIBFTBIN	:=	$(LIBFTDIR)/libft.a

CC			:=	cc
RM			:=	rm -rf
AR			:=	ar -rcs
CFLAGS		:=	-Wall -Werror -Wextra
RLFLAGS		:=	-lreadline
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

MODULES		:=	buildins \
				parser \
				exec \
				free \
				open \
				init \
				error \
				utils

FILES 		= 	minishell.c \
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

SRCS		=	$(addprefix $(SRCSDIR)/, $(FILES))
OBJS		=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))

INCS	 	=	$(foreach hdir, $(INCSDIR), -I $(hdir))
INCS	 	+=	$(foreach hdir, $(LIBFTDIR)/$(INCSDIR), -I $(hdir))
RLLIB		:=	-L ~/.brew/Cellar/readline/8.2.10/lib
RLINC		:=	-I ~/.brew/Cellar/readline/8.2.10/include

F			=	============================================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

all: $(LIBFTBIN) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(RLINC) $(RLLIB) $(RLFLAGS) $^ $(LIBFTBIN) -o $@
	@printf "$(V)\nSuccessfully compiled binary $(G)$(B)$(NAME)$(T)"
	@printf "$(V) and $(G)$(B)$(CNTR)$(V) object file(s).$(T)\n"
	@printf "$(G)$(B)\n$(F)$(T)\n" && make finish

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(RLINC) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(Y)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		printf "✅$(T)$(V) $<$(T) $(C)      \t🔀\t$(G)$(B)$@$(T)\n"; else \
		make title; printf "✅$(T)$(V) $<$(T) $(C)      \t🔀\t$(G)$(B)$@$(T)\n"; fi

title:
	@printf "$(C)                                   $(R)$(B)                  ╱|、$(T)\n"
	@printf "$(C)╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦              $(R)$(B)                 (\` - 7$(T)\n"
	@printf "$(C)║║║║║║║║╚═╗╠═╣║╣ ║  ║   by vkinaret$(R)$(B)                 |、⁻〵$(T)\n"
	@printf "$(C)╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝  & jmertane$(R)$(B)                 じしˍ,)ノ$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"
	@printf "$(V)Using compiler $(G)$(B)$(CC)$(T)$(V) with flags: $(G)$(B)$(CFLAGS)$(T)\n\n"

finish:
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(LIBFTBIN):
	@make --quiet -C $(LIBFTDIR) all

clean:
	@$(SCREENCLR) && echo "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(LIBFTDIR)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@make --quiet -C $(LIBFTDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT)
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!$(T)" && $(SLEEP)

fclean: clean
	@echo "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(LIBFTDIR)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(NAME)$(T)\n"
	@make --quiet -C $(LIBFTDIR) fclean
	@$(RM) $(NAME)
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!\n$(T)" && $(SLEEP)

re:
	@make fclean
	@make all

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all debug clean fclean re nm title finish
