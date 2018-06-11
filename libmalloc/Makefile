# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/12 15:16:17 by jwalsh            #+#    #+#              #
#    Updated: 2018/06/11 12:57:53 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# export DIR_MALLOC := libmalloc
# export DIR_LIB		:= $(DIR_MALLOC)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SYM_NAME := libft_malloc.so

SRCS := testFunction

EXT  :=.c
SRCS := $(addsuffix $(EXT), $(SRCS))
OBJS := $(SRCS:.c=.o)
SRCS_DIR := ./src
OBJS_DIR := ./obj
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

HEADERS := header.h
HEADER_DIR := ./inc/
HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

CC := gcc
CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -shared $^ -o $(NAME)
	@rm -f $(SYM_NAME)
	@ln -s $(NAME) $(SYM_NAME)
	@echo libft_malloc compiled and linked

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) -fPIC -I$(HEADER_DIR) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "libft_malloc clean"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(SYM_NAME)
	@echo "libft_malloc fclean"

re: fclean all

PHONY: re all clean fclean

.PHONY: all clean fclean re