/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:34:06 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/08 15:38:07 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 50
# define KEY_ESC 65307
# define ICON_SIZE 40
# define I 40
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <fcntl.h>
# include <errno.h>
# include "get_next_line.h"

typedef struct t_struct
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*player_ptr;
	void	*wall_ptr;
	void	*floor_ptr;
	void	*collect_ptr;
	void	*exit_ptr;

	char	**map;
	char	**map_copy;

	int		map_width;
	int		map_height;
	int		fd;
	int		count_player;
	int		count_exit;
	int		temp_exit;
	int		count_lines;
	int		count_collect;
	int		temp_collect;
	int		count_steps;
	int		player_x;
	int		player_y;
	int		x_axis;
	int		y_axis;

}	t_struct;

int		flood_fill(t_struct *game, int y, int x);
int		read_map(t_struct *game, char *map);
int		copy_map(t_struct *game, char *map);
int		check_map(t_struct *game);
void	freemap(char **map);
int		on_destroy(t_struct *data);
void	set_images(t_struct *game);
void	place_images(t_struct *game);
int		on_keypress(int keysym, t_struct *data);
void	is_collectable(t_struct *data, int y, int x);
void	free_maps(t_struct *game);
int		check_walls(t_struct *game);
int		check_exit(t_struct *game);
int		check_colective(t_struct *game);
int		check_player(t_struct *game);
int		check_char(t_struct *game);

#endif