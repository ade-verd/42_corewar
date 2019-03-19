# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 12:33:34 by ade-verd          #+#    #+#              #
#    Updated: 2019/03/08 18:05:11 by ade-verd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary
NAME = rasm

# Compiler
CC = gcc

# Directories
PROJECT_PATH = ../
SRC_PATH = src/
OBJ_PATH = obj/
SCRIPTS_PATH = $(PROJECT_PATH)scripts/
PRINTF_PATH = $(PROJECT_PATH)libftprintf/
LIBFT_PATH = $(PRINTF_PATH)libft/
LIB_PATH = $(LIBFT_PATH) $(PRINTF_PATH)
INC_PATH = $(PROJECT_PATH)includes/ \
		   $(addsuffix includes/, $(LIB_PATH))

# Includes & libraries
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = $(addprefix -L ,$(LIB_PATH))
LDLIBS = -lft -lftprintf

DEPENDENCIES = 	$(PROJECT_PATH)includes/op.h\
				$(PROJECT_PATH)includes/rasm.h\

# Prerequisites
PREREQUISITES_NAME = 	\

PREREQUISITES = $(addprefix $(SCRIPTS_PATH), $(PREREQUISITES_NAME))

# Sources
SRC_NAME = 	\
			rasm.c\
			instr.c\
			head.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags with OS Compatibiliy
OS = $(shell uname)
ifeq ($(OS), Darwin)
	FLAGS_DEFAULT = -Werror -Wall -Wextra
endif
ifeq ($(OS), Linux)
	FLAGS_DEFAULT = -Wno-unused-result
endif
ifdef FLAGS
	ifeq ($(FLAGS), no)
		CFLAGS := $(ADDFLAGS)
	endif
	ifeq ($(FLAGS), debug)
		CFLAGS := $(FLAGS_DEFAULT) -ansi -pedantic -g $(ADDFLAGS)
	endif
else
	CFLAGS := $(FLAGS_DEFAULT) $(ADDFLAGS)
endif

# MAKEFLAGS
MAKE = make | perl -ne '$|=1; print unless /nothing to be done|up to date/i'
MAKEC = make -s --no-print-directory -C

# Variables
COUNTER=0

# **************************************************************************** #
# SPECIALS CHARS                                                               #
# **************************************************************************** #
LOG_CLEAR = \033[2K
LOG_UP = \033[A
LOG_NOCOLOR = \033[0m
LOG_BOLD = \033[1m
LOG_UNDERLINE = \033[4m
LOG_BLINKING = \033[5m
LOG_BLACK = \033[1;30m
LOG_RED = \033[1;31m
LOG_GREEN = \033[1;32m
LOG_YELLOW = \033[1;33m
LOG_BLUE = \033[1;34m
LOG_VIOLET = \033[1;35m
LOG_CYAN = \033[1;36m
LOG_WHITE = \033[1;37m

TITLE = $(LOG_CLEAR)$(LOG_BLUE)
END_TITLE = $(LOG_NOCOLOR)
LINKING = "--$(LOG_CLEAR)$(LOG_GREEN)✓$(LOG_NOCOLOR)\tlinking " \
				".................. $(LOG_VIOLET)$<$(LOG_NOCOLOR)"
ASSEMBLING = "--$(LOG_CLEAR)$(LOG_GREEN)✓$(LOG_NOCOLOR)\tassembling " \
			 	"............... $(LOG_YELLOW)$(NAME)$(LOG_NOCOLOR)"
OBJECTS_DEL = "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion " \
				"............ $(LOG_RED)×$(LOG_NOCOLOR)"
BIN_DEL = "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion " \
				"............. $(LOG_RED)×$(LOG_NOCOLOR)"

# **************************************************************************** #
# RULES                                                                        #
# **************************************************************************** #
.PHONY: all, clean, fclean, re, norme, norm, \
		prerequisites, libft, libftprintf.a \
		init_submodule update_submodule

all: $(NAME)

$(NAME): prerequisites $(OBJ_PATH) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@if [ $(COUNTER) -ne 0 ]; then echo -e $(ASSEMBLING); fi;

prerequisites:
	@$(foreach PREREQUISITES_NAME, $(PREREQUISITES_NAME), $(PREREQUISITES);)
	@make libftprintf.a

libft:
	@make libftprintf.a

libftprintf.a:
	@$(MAKEC) $(PRINTF_PATH) $@

$(OBJ_PATH):
	@echo -e "$(TITLE)build $(NAME)$(END_TITLE)"
	@echo -e "--$(LOG_CLEAR)Flags : $(CFLAGS)"
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPENDENCIES)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo -e $(LINKING)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))

clean:
	@echo -e "$(TITLE)clean $(NAME)$(END_TITLE)"
	@echo -e $(OBJECTS_DEL)
	@rm -Rf $(OBJ_PATH)
	@$(MAKEC) $(PRINTF_PATH) clean_quiet

fclean:
	@echo -e "$(TITLE)fclean $(NAME)$(END_TITLE)"
	@echo -e $(OBJECTS_DEL)
	@rm -Rf $(OBJ_PATH)
	@echo -e $(BIN_DEL)
	@rm -f $(NAME)
	@$(MAKEC) $(PRINTF_PATH) fclean_quiet

re: fclean all

norme:
	norminette $(SRC)
	norminette $(DEPENDENCIES)

norm:
	make norme | grep -B 1 "Error\|Warning" || echo "norme OK"
