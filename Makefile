# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/10 13:28:27 by jwalsh            #+#    #+#              #
#    Updated: 2018/06/21 11:39:03 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := test

LIB_NAME := ft_malloc
LIB_PATH := libmalloc/
LIB_INC := $(LIB_PATH)inc

SRC := test10.c

CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -I$(LIB_INC) -L$(LIB_PATH) -l$(LIB_NAME) 
	# @$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "test compiled"

clean: 
	@rm -f $(NAME)
	@echo "test clean"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@echo "test fclean"

re: fclean all