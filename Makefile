# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/17 23:21:27 by vpailhe           #+#    #+#              #
#    Updated: 2015/03/14 17:40:14 by vpailhe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_minishell1

SRC = ft_minishell1.c\
	  exec.c\
	  display.c\
	  parsing.c\
	  launch_cd.c\
	  launch_env.c\
	  get_next_line.c\
	  launch_unsetenv.c\

OBJ = ft_minishell1.o\
	  exec.o\
	  display.o\
	  parsing.o\
	  launch_cd.o\
	  launch_env.o\
	  get_next_line.o\
	  launch_unsetenv.o\

FLAG = -Wall -Wextra -Werror

INC = -I /usr/X11/include/X11

.PHONY : libft.a

all : libft.a $(NAME)

libft.a:
	@$(MAKE) -C ./libft

$(OBJ):
	gcc -c $(SRC) $(FLAG) libft/libft.a -I ./libft -ggdb

$(NAME): $(OBJ)
	gcc $(OBJ)  $(FLAG) libft/libft.a -I ./libft -o $(NAME) -ggdb

%.o: %.c
	gcc -I ./libft/includes -c $@ $^ 

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
