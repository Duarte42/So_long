# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 16:26:35 by duamarqu          #+#    #+#              #
#    Updated: 2024/04/24 14:35:34 by duamarqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= so_long

CC= cc

CFLAGS= -Wall -Wextra -Werror -Iinclude
SRCS_PATH	= src
SRC= $(wildcard $(SRCS_PATH)/*.c)
OBJ= $(SRC:.c=.o)	
MLX= include/mlx_linux/libmlx.a
MLXFLAGS= -Lmlx_linux -lz -lXext -lX11 -lm

all: $(NAME)

$(MLX):
			make -C ./include/mlx_linux

$(NAME):	$(OBJ) $(MLX) 
			$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME) -g


clean:
			rm -f $(OBJ) && make clean -C include/mlx_linux

fclean: 	clean
			rm -f $(NAME) ${OBJ} && make clean -C include/mlx_linux


re:			fclean all

.PHONY:		all clean fclean re