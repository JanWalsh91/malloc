# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/12 15:16:17 by jwalsh            #+#    #+#              #
#    Updated: 2018/06/16 11:10:04 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SYM_NAME := libft_malloc.so

SRCS := malloc \
		realloc \
		free \
		region_manager \
		block_manager \
		show_alloc_mem \
		putbase

EXT  :=.c
SRCS := $(addsuffix $(EXT), $(SRCS))
OBJS := $(SRCS:.c=.o)
SRCS_DIR := ./src
OBJS_DIR := ./obj
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

HEADERS := malloc.h
HEADER_DIR := ./inc/
HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))
LIBFT := libft.a
LIBFT_PATH := libft/
LIBFT_INC_PATH := libft/inc/

CC := gcc
CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I$(LIBFT_INC_PATH) -L$(LIBFT_PATH) -lft -shared $^ -o $(NAME)
	@rm -f $(SYM_NAME)
	@ln -s $(NAME) $(SYM_NAME)
	@echo libft_malloc compiled and linked

$(OBJS): | $(OBJS_DIR) $(LIBFT_PATH)$(LIBFT)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@make -s -C $(LIBFT_PATH)
	@$(CC) -fPIC -I$(HEADER_DIR) -I$(LIBFT_INC_PATH) $(CFLAGS) -o $@ -c $<

$(LIBFT_PATH)$(LIBFT):
	@make -s -C $(LIBFT_PATH)

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