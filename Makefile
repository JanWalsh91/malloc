# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/10 13:28:27 by jwalsh            #+#    #+#              #
#    Updated: 2018/06/10 15:04:36 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export LD_LIBRARY_PATH := ./libmalloc:$LD_LIBRARY_PATH

NAME := test

LIB_NAME := ft_malloc
LIB_PATH := libmalloc/
LIB_INC := $(LIB_PATH)inc

SRC := main.c

CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -I$(LIB_INC) -L$(LIB_PATH) -l$(LIB_NAME) 

clean: 
	@rm -f $(NAME)
	@echo "clean test"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@echo "fclean test"

re: fclean all