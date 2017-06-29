# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/06 14:23:18 by niludwig          #+#    #+#              #
#    Updated: 2017/06/29 22:47:18 by rvan-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_EX = asm
ASM_FILE = asm_check_body.c \
			asm_check_param.c \
			asm_complete_file.c \
			asm_finalize.c \
			asm_get_param.c \
			asm_pars_body.c \
			asm_pars_header.c \
			asm_print_body.c \
			asm_print_file.c \
			ft_putstr_fd_on.c \
			utilites_second.c \
			utilities.c \
			asm.c
ASM_OBJ = $(ASM_FILE:.c=.o)
ASM_DIR = ./assembleur/src/
ASM_OBJ_DIR = ./assembleur/dst/
ASM_SRC = $(addprefix $(ASM_DIR),$(ASM_FILE))
ASM_DST = $(addprefix $(ASM_OBJ_DIR),$(ASM_OBJ))

VM_EX = corewar
VM_FILE = affichage.c \
			get_info.c \
			init.c \
			instructab.c \
			get_params.c \
			rd_rw.c \
			main.c \
			set_global.c \
			load_players.c \
			instructions/ft_live.c \
			instructions/ft_ld.c \
			instructions/ft_st.c \
			instructions/ft_add.c \
			instructions/ft_sub.c \
			instructions/ft_and.c \
			instructions/ft_or.c \
			instructions/ft_xor.c \
			instructions/ft_zjmp.c \
			instructions/ft_ldi.c \
			instructions/ft_sti.c \
			instructions/ft_fork.c \
			instructions/ft_lld.c \
			instructions/ft_lldi.c \
			instructions/ft_lfork.c \
			instructions/ft_aff.c
VM_OBJ = $(VM_FILE:.c=.o)
VM_DIR = ./vm/src/
VM_OBJ_DIR = ./vm/dst/
VM_SRC = $(addprefix $(VM_DIR),$(VM_FILE))
VM_DST = $(addprefix $(VM_OBJ_DIR),$(VM_OBJ))

OP_C = ./include/op.c
OP_O = ./include/op.o
CC = gcc
CFLAG = -Wall -Werror -Wextra

LIBFT_PATH = ./libft/
LIBFT = ./libft.a
RM = rm -f

all: $(VM_EX) $(ASM_EX)

$(ASM_EX): $(ASM_DST) $(OP_O)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) -o $(ASM_EX) $(ASM_DST) $(OP_O) -I./include -L. $(LIBFT_PATH)$(LIBFT)

$(VM_EX) : $(VM_DST) $(OP_O)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) -o $(VM_EX) $(VM_DST) $(OP_O) -I./include -L. $(LIBFT_PATH)$(LIBFT) -lncurses

$(OP_O): $(OP_C)
	@$(CC) $(CFLAG) -o $@ -c $< -I./include

$(VM_OBJ_DIR)%.o: $(VM_DIR)%.c
	-@mkdir -p $(VM_OBJ_DIR)
	-@mkdir -p $(VM_OBJ_DIR)/instructions
	@$(CC) $(CFLAG) -o $@ -c $< -I./include

$(ASM_OBJ_DIR)%.o: $(ASM_DIR)%.c
	-@mkdir -p $(ASM_OBJ_DIR)
	@$(CC) $(CFLAG) -o $@ -c $< -I./include

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(ASM_DST)
	@$(RM) $(VM_DST)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(ASM_EX)
	@$(RM) $(VM_EX)

re: fclean all
