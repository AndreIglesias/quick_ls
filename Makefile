#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:07 by ciglesia          #+#    #+#              #
#    Updated: 2021/07/04 01:11:21 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls

#****************** INC *******************#
# General
INC			=	./include/

# Lib
LIB			=	./libft/
LIBINC		=	$(LIB)/include/

LIBSTD		=	$(LIB)/libstd/
LIBSTR		=	$(LIB)/libstring/
LIBALG		=	$(LIB)/libalgorithm/

INC_LIB		=	-L$(LIBALG) -lalgorithm -L$(LIBSTD) -lstd -L$(LIBSTR) -lstring

INCLUDE		=	-O3 -I $(INC) -I $(LIBINC)

#***************** SRC ********************#

DIRSRC		=	./src/
DIRENT		=	$(DIRSRC)/dirent/
DIREVAL		=	$(DIRSRC)/eval/

SRC			=	main.c
DRNT		=	types.c
EVAL		=	ft_ls.c sort.c

SRCS		=	$(SRC) $(DRNT) $(EVAL)

#***************** DEPS ******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

ifndef VERBOSE
.SILENT:
endif

CC			=	/usr/bin/clang
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e
BOLD		=	"\e[1m"
BLINK		=	 "\e[5m"
RED			=	 "\e[38;2;255;0;0m"
GREEN		=	 "\e[92m"
BLUE		=	 "\e[34m"
YELLOW		=	 "\e[33m"
E0M			=	 "\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				@printf $(GREEN)"Generating ft_ls objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRENT)/%.c
				@printf $(GREEN)"Generating ft_ls objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIREVAL)/%.c
				@printf $(GREEN)"Generating ft_ls objects... %-33.33s\r"$(E0M) $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(NAME)	:		ftlib $(OBJS)
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
				@$(ECHO) "▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒"
				@$(ECHO) "▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒"
				@$(ECHO) "░█▀█▀█░█▀██░█▀█░█▄█▄█░░█▀█▀█░█▀██░█▀█░█▄█▄█░░█▀█▀█░█▀██░█▀█░█▄█▄█░"
				@$(ECHO) "░█▀█▀█░█▀████▀█░█▄█▄█░░█▀█▀█░█▀████▀█░█▄█▄█░░█▀█▀█░█▀████▀█░█▄█▄█░"
				@$(ECHO) "████████▀█████████████████████▀█████████████████████▀█████████████"
				@$(ECHO) $(BOLD)$(GREEN)'> ft_ls Compiled'$(E0M)

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(LIB) && $(MAKE) clean)
				@$(ECHO) $(BOLD)$(RED)'> ft_ls directory        cleaned'$(E0M)

all		:		$(NAME)

fclean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@($(RM) $(NAME))
				@(cd $(LIB) && $(MAKE) fclean)
				@$(ECHO) $(BOLD)$(RED)'> ft_ls directory        cleaned'$(E0M)
				@$(ECHO) $(BOLD)$(RED)'> Executable             removed'$(E0M)

re		:		fclean all

ftlib	:
				@(cd $(LIB) && $(MAKE))

.PHONY	:		all clean fclean re ftlib

-include $(DEPS)
