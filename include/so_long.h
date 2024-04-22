#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <fcntl.h>
#include <errno.h>
#include "get_next_line.h"

#ifndef WINDOW_H
#define WINDOW_H

typedef struct t_struct
{
	void *mlx_ptr;
	void *win_ptr;
	void *player_ptr;
	void *wall_ptr;
	void *floor_ptr;
	void *collect_ptr;
	void *exit_ptr;

	char **map;
	char **map_copy;

	int map_width;
	int map_height;
	int fd;
	int count_player;
	int count_exit;
	int temp_exit;
	int count_lines;
	int count_collect;
	int temp_collect;
	int count_steps;
	int player_x;
	int player_y;
	int x_axis;
	int y_axis;

} t_struct;

int read_map(t_struct *game);
int copy_map(t_struct *game);
int check_map(t_struct *game);
#endif