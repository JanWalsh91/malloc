# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/12 15:16:17 by jwalsh            #+#    #+#              #
#    Updated: 2018/07/05 15:54:34 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
ALL_NAMES := libft_malloc*.so
SYM_NAME := libft_malloc.so

SRCS := malloc \
		realloc \
		free \
		calloc \
		region_manager \
		region_manager2 \
		region_manager3 \
		region_manager4 \
		block_manager \
		block_manager2 \
		show_alloc_mem \
		putbase \
		errors \
		scribble \
		align16

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
CFLAGS := -Wall -Werror -Wextra -g

C_NONE = \033[0m
C_BOLD = \033[1m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_BROWN = \033[33m
C_BLUE = \033[34m
C_MAGENTA = \033[35m
C_CYAN = \033[36m
C_GRAY = \033[37m

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) -I$(LIBFT_INC_PATH) -L$(LIBFT_PATH) -lft -shared $^ -o $(NAME) -lpthread
	@ln -fs $(NAME) $(SYM_NAME)
	@echo "$(C_GREEN)Libft_malloc compiled$(C_NONE)"
	@echo "$(C_MAGENTA)Libft_malloc linked$(C_NONE)"

$(OBJS): | $(OBJS_DIR) $(LIBFT_PATH)$(LIBFT)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@make -s -C $(LIBFT_PATH)
	@$(CC) -fPIC -I$(HEADER_DIR) -I$(LIBFT_INC_PATH) $(CFLAGS) -o $@ -c $< -fvisibility=hidden
 
$(LIBFT_PATH)$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(C_GREEN)Libft_malloc clean$(C_NONE)"
	@make clean -C $(LIBFT_PATH) 

fclean: clean
	@rm -f $(NAME)
	@rm -f $(SYM_NAME)
	@rm -f $(ALL_NAMES)
	@make fclean -C $(LIBFT_PATH) 
	@echo "$(C_GREEN)Libft_malloc fclean$(C_NONE)"

re: fclean all

PHONY: re all clean fclean

.PHONY: all clean fclean re