# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opletsan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/13 21:36:02 by opletsan          #+#    #+#              #
#    Updated: 2018/10/14 13:20:56 by opletsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/
INC_DIR		=	./inc/ ./printf/inc ./libft/inc
LIB_DIR		=	./libft/ ./printf/

LFT			=	./libft/libft.a
LPRINTF		=	./printf/libftprintf.a
HEADER		=	./inc/lem_in.h
SRC 		=   algorithm.c \
				read_links.c \
				read_rooms.c \
				main.c
OBJ			=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))

LIB			=	$(addprefix -L,$(LIB_DIR))
INC			=	$(addprefix -I,$(INC_DIR))
MK_LFT		=	-C ./libft/
MK_LPRINTF	=	-C ./printf/

CFLAGS		=	-Wall -Werror -Wextra
LFLAGS		=	-lft -lftprintf

TG			=	"\033[32m"
TR			=	"\033[31m"
TU			=	"\033[4m"
EOC			=	"\033[0m"

all: $(NAME)

$(NAME): $(LFT) $(LPRINTF) $(OBJ)
	@gcc $(LFLAGS) $(LIB) $(OBJ) -o $@
	@echo ${TG}"[✓] "${TU}"$@"${EOC}

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: %.c $(HEADER)
	@gcc $(CFLAGS) $(INC) -c $< -o $@
	@echo ${TG}"[✓] $<"${EOC}

$(LFT):
	@make $(MK_LFT)

$(LPRINTF):
	@make $(MK_LPRINTF)

clean:
	@make clean $(MK_LFT)
	@make clean $(MK_LPRINTF)
	@rm -f $(OBJ)
	@echo ${TR}"[✗] $(OBJ)"${EOC}

fclean: clean
	@make fclean $(MK_LFT)
	@make fclean $(MK_LPRINTF)
	@rm -f $(NAME)
	@echo ${TR}"[✗] "${TU}"$(NAME)"${EOC}

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
