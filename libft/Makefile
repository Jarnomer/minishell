# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 10:37:44 by jmertane          #+#    #+#              #
#    Updated: 2024/05/04 19:38:00 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
OBJSDIR		:=	build
DEPSDIR		:=	.deps
ERRORTXT	:=	error.txt

CC			:=	cc
RM			:=	rm -rf
AR			:=	ar -rcs
CFLAGS		:=	-Wall -Werror -Wextra
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d
SLEEP		:=	sleep .1

FILES		:= 	ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isascii \
				ft_isprint \
				ft_bzero \
				ft_calloc \
				ft_memset \
				ft_memcpy \
				ft_memmove \
				ft_memchr \
				ft_memcmp \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_strlen \
				ft_strlcpy \
				ft_strlcat \
				ft_strchr \
				ft_strrchr \
				ft_strncmp \
				ft_strnstr \
				ft_strdup \
				ft_substr \
				ft_strjoin \
				ft_strtrim \
				ft_split \
				ft_atoi \
				ft_itoa \
				ft_toupper \
				ft_tolower \
				ft_strmapi \
				ft_striteri \
				ft_printf \
				ft_printf_fmt \
				ft_gnl \
				ft_gnl_utils

HEADERS		:=	libft \
				ft_printf \
				ft_gnl

SRCS		:=	$(addsuffix .c, $(FILES))
HDRS		:=	$(addsuffix .h, $(HEADERS))
OBJS		=	$(patsubst %.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		=	$(patsubst %.c, $(DEPSDIR)/%.d, $(SRCS))

F			=	=================================================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m
#
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(G)$(B)\t\t\t\t\t\t\t\t|\n$(F)$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(NAME)$(T)\n\n"

$(OBJSDIR)/%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKEFILE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(Y)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		printf "✅$(T)$(V) $<$(T) $(C)    \t🔀\t$(G)$(B)./libft/$@  \t|$(T)\n"; else \
		printf "$(C)$(B)\n"; \
		printf "╦  ╦╔╗ ╔═╗╔╦╗\n"; \
		printf "║  ║╠╩╗╠╣  ║\n"; \
		printf "╩═╝╩╚═╝╚   ╩  by jmertane\n"; \
		printf "$(G)$(B)$(F)\n\t\t\t\t\t\t\t\t|$(T)\n"; \
		printf "✅$(T)$(V) $<$(T) $(C)    \t🔀\t$(G)$(B)./libft/$@  \t|$(T)\n"; fi

clean:
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all clean fclean re
