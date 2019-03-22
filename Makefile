# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 13:46:57 by ade-verd          #+#    #+#              #
#    Updated: 2019/03/22 17:03:39 by ade-verd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary
NAME = asm_and_corewar_and_rasm
NAME_ASM = asm
NAME_CW = corewar
NAME_RASM = rasm

SUBMOD = submodules

# Directories
ASM_PATH = assembler
CW_PATH = vm
RASM_PATH = rassembler
PRINTF_PATH = libftprintf/

# MAKEFLAGS
MAKEFLAG += --no-print-directory
MAKE = make $(MAKEFLAG) -C

# **************************************************************************** #
# SPECIALS CHARS                                                               #
# **************************************************************************** #
LOG_CLEAR = \033[2K
LOG_NOCOLOR = \033[0m
LOG_RED = \033[1;31m
LOG_BLUE = \033[1;34m
LOG_YELLOW = \033[1;33m

TITLE = $(LOG_CLEAR)$(LOG_BLUE)
END_TITLE = $(LOG_NOCOLOR)
BIN_DEL = "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion " \
				"............. $(LOG_RED)×$(LOG_NOCOLOR)"

# **************************************************************************** #
# RULES                                                                        #
# **************************************************************************** #
.PHONY: all
all: $(NAME)

.PHONY: $(NAME)
$(NAME): submod_update $(NAME_ASM) $(NAME_CW) $(NAME_RASM)

.PHONY: $(NAME_ASM)
$(NAME_ASM): force
	@$(MAKE) $(ASM_PATH) $@
	@if [ -h $@ ]; then rm -f $@; fi;
	@if [ -f $(ASM_PATH)/$@ ]; then ln -s $(ASM_PATH)/$@ .; fi;

.PHONY: $(NAME_CW)
$(NAME_CW): force
	@$(MAKE) $(CW_PATH) $@
	@if [ -h $@ ]; then rm -f $@; fi;
	@if [ -f $(CW_PATH)/$@ ]; then ln -s $(CW_PATH)/$@ .; fi;

.PHONY: $(NAME_RASM)
$(NAME_RASM): force
	@$(MAKE) $(RASM_PATH) $@
	@if [ -h $@ ]; then rm -f $@; fi;
	@if [ -f $(RASM_PATH)/$@ ]; then ln -s $(RASM_PATH)/$@ .; fi;

.PHONY: libft
libft:
	@make libftprintf.a

.PHONY: libftprintf.a
libftprintf.a:
	@$(MAKE) $(PRINTF_PATH) $@

.PHONY: force
force:
	@true

.PHONY: clean
clean:
	@$(MAKE) $(ASM_PATH) clean
	@$(MAKE) $(CW_PATH) clean
	@$(MAKE) $(RASM_PATH) clean

.PHONY: fclean
fclean:
	@$(MAKE) $(ASM_PATH) fclean
	@$(MAKE) $(CW_PATH) fclean
	@$(MAKE) $(RASM_PATH) fclean
	@if [ -h $(NAME_ASM) ]; then rm -f $(NAME_ASM); fi;
	@if [ -h $(NAME_CW) ]; then rm -f $(NAME_CW); fi;
	@if [ -h $(NAME_RASM) ]; then rm -f $(NAME_RASM); fi;

.PHONY: re
re: fclean all

.PHONY: norme
norme:
	@echo -e "$(TITLE)Norminette: $(NAME_ASM)$(END_TITLE)"
	@$(MAKE) $(ASM_PATH) norme
	@echo -e "$(TITLE)Norminette: $(NAME_CW)$(END_TITLE)"
	@$(MAKE) $(CW_PATH) norme
	@echo -e "$(TITLE)Norminette: $(NAME_RASM)$(END_TITLE)"
	@$(MAKE) $(RASM_PATH) norme

.PHONY: norm
norm:
	@echo -e "$(TITLE)Norminette: $(NAME_ASM)$(END_TITLE)"
	@$(MAKE) $(ASM_PATH) norm
	@echo -e "$(TITLE)Norminette: $(NAME_CW)$(END_TITLE)"
	@$(MAKE) $(CW_PATH) norm
	@echo -e "$(TITLE)Norminette: $(NAME_RASM)$(END_TITLE)"
	@$(MAKE) $(RASM_PATH) norm

.PHONY: submod_init
submod_init:
	@echo -e "$(TITLE)Init submodules$(END_TITLE)"
	git submodule update --init --recursive

.PHONY: submod_update
submod_update: submod_init
	@echo -e "$(TITLE)Update submodules$(END_TITLE)"
	git submodule update --recursive --remote

.PHONY: submod_checkid
submod_checkid:
	@echo -e "$(TITLE)Submodules commit ID$(END_TITLE)"
	git submodule ; git submodule foreach git submodule
	@echo "---------"
	cat $(SUBMOD)

.PHONY: submod_checkid
submod_saveid: submod_init submod_update
	@echo -e "$(TITLE)Save submodules commit ID into \"$(SUBMOD)\"$(END_TITLE)"
	@git submodule > $(SUBMOD)
	@git submodule foreach git submodule >> $(SUBMOD)
	@cat $(SUBMOD)
