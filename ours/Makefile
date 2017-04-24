# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/06 14:23:18 by niludwig          #+#    #+#              #
#    Updated: 2017/04/20 05:16:03 by joeyplevy        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
VM = corewar
CC = gcc
CFLAG = -Wall -Werror -Wextra
# ASMSRC = ./assembleur/src/main_asm.c ./include/op.c
# ASMOBJ = $(ASMSRC:.c=.o)
VMSRC = ./vm/test_ncurses.c ./include/op.c
VMOBJ = $(VMSRC:.c=.o)
LIBFT_PATH = ./libft/libft/
PRINTF_PATH = ./libft/
PRINTF = ./libft/libftprintf.a
LIBFT = ./libft/libft/libft.a
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: $(VM)

$(ASM): $(ASMOBJ)
	@$(MAKE) -C $(PRINTF_PATH)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) -o $(ASM) $(ASMOBJ) -I./include -L. $(LIBFT) $(PRINTF)

$(VM) : $(VMOBJ)
	@$(MAKE) -C $(PRINTF_PATH)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) -o $(VM) $(VMOBJ) -I./include -L. $(LIBFT) $(PRINTF) -lncurses

%.o: %.c
	@$(CC) $(CFLAG) -o $@ -c $< -I./include

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(ASMOBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(ASM)

re: fclean all
