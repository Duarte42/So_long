# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 16:26:35 by duamarqu          #+#    #+#              #
#    Updated: 2024/05/27 14:55:02 by duamarqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= so_long

CC= cc

CFLAGS= -Wall -Wextra -Werror -Iinclude
SRCS_PATH	= src
SRC= $(wildcard $(SRCS_PATH)/*.c)
OBJ= $(SRC:.c=.o)	
MLX= include/minilibx-linux/libmlx.a
MLXFLAGS= -Lminilibx-linux -lz -lXext -lX11 -lm

all: $(NAME)

$(MLX):
			make -C ./include/minilibx-linux

$(NAME):	$(OBJ) $(MLX) 
			$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME) -g


clean:
			rm -f $(OBJ) && make clean -C include/minilibx-linux

fclean: 	clean
			rm -f $(NAME) ${OBJ} && make clean -C include/minilibx-linux


re:			fclean all

.PHONY:		all clean fclean re