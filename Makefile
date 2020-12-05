# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/05 14:19:32 by kfriese           #+#    #+#              #
#    Updated: 2020/12/05 14:19:34 by kfriese          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
FLAGS = -Wall -Wextra -Werror -I/usr/local/include -L/usr/local/lib \
		-framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -lmlx main.c
