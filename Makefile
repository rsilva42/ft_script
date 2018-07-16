# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:44:31 by rsilva            #+#    #+#              #
#    Updated: 2018/07/11 03:56:51 by rsilva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = ft_script

CCFLAGS = -c -Wall -Wextra -Werror
SRCS = sources/ft_script.c sources/helpers.c sources/ft_forkpty.c sources/printer.c
OBJS = objects/ft_script.o objects/helpers.o objects/ft_forkpty.o objects/printer.o
INCLS = includes

all: $(NAME)

objects/%.o: sources/%.c
	@/bin/mkdir -p objects
	gcc -c -I$(INCLS) $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
