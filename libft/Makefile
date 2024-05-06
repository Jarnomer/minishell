# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 10:37:44 by jmertane          #+#    #+#              #
#    Updated: 2024/05/06 15:25:56 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
OBJSDIR		:=	objs
INCSDIR		:=	incs
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps
ERRORTXT	:=	error.txt

CC			:=	cc
RM			:=	rm -rf
AR			:=	ar -rcs
CFLAGS		:=	-Wall -Werror -Wextra
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d
SLEEP		:=	sleep .1

FILES		:= 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_memset.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_printf.c \
				ft_printf_fmt.c \
				ft_gnl.c \
				ft_gnl_utils.c

SRCS		=	$(addprefix $(SRCSDIR)/, $(FILES))
OBJS		=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))

INCS 		=	$(foreach dir, $(INCSDIR), -I $(dir))

F			=	============================================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS) && $(SLEEP)
	@printf "$(V)\nSuccessfully compiled binary $(G)$(B)$(NAME)$(T)"
	@printf "$(V) and $(G)$(B)$(CNTR)$(V) object file(s).$(T)\n"
	@printf "$(G)$(B)\n$(F)$(T)\n\n"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(Y)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		printf "✅$(T)$(V) $<$(T) $(C)       \t🔀\t$(G)$(B)$@$(T)\n"; else \
		make title; printf "✅$(T)$(V) $<$(T) $(C)       \t🔀\t$(G)$(B)$@$(T)\n"; fi

title:
	@printf "$(C)                         $(R)$(B)                            ╱|、$(T)\n"
	@printf "$(C)╦  ╦╔╗ ╔═╗╔╦╗            $(R)$(B)                           (˚ˎ 。7$(T)\n"
	@printf "$(C)║  ║╠╩╗╠╣  ║             $(R)$(B)                           |、˜〵$(T)\n"
	@printf "$(C)╩═╝╩╚═╝╚   ╩  by jmertane$(R)$(B)                           じしˍ,)ノ$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"
	@printf "$(V)Using compiler $(G)$(B)$(CC)$(T)$(V) with flags: $(G)$(B)$(CFLAGS)$(T)\n\n"

clean:
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all clean fclean re title
