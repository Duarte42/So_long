//#include "../include/mlx_linux/mlx.h"
#include "../include/so_long.h"
//#include "../include/get_next_line.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <X11/X.h>
// #include <X11/keysym.h>


int	on_destroy(t_struct *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
int	on_keypress(int keysym, t_struct *data)
{
	(void)data;
	printf("Pressed the key: %d\n", keysym);
	if (keysym == 65307)                 //EXIT KEY
		on_destroy(data);
	return (0);
}

void *ft_memset(void *ptr, int ch, size_t n)
{
	size_t i;
	char *str;

	str = (char *)ptr;
	i = 0;
	while (i < n)
	{
		str[i] = ch;
		i++;
	}
	return (str);
}
int flood_fill(t_struct *game, int y, int x)
{
	if(game->map_copy[y][x] == 'I')
		return (0);
	else if (game->map_copy[y][x] == 'E')
		game->temp_exit++;
	else if (game->map_copy[y][x] == 'C')
		game->temp_collect++;
	game->map_copy[y][x] = 'I';
	flood_fill(game, y + 1, x);
	flood_fill(game, y - 1, x);
	flood_fill(game, y, x + 1);
	flood_fill(game, y, x - 1);
	return (1);
}

void set_images(t_struct *game)
{
	int w;
	int h;

	w = SIZE * 2;
	h = SIZE / 2;

	game->floor_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "./image/floor.xpm", &w, &h);
	game->wall_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "./image/wall.xpm", &w, &h);
	game->collect_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "./image/collective.xpm", &w, &h);
	game->player_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "./image/player.xpm", &w, &h);
	game->exit_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "./image/exit.xpm", &w, &h);
}

void place_images(t_struct *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while(game->map[y][x])
		{
			if(game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall_ptr, x * SIZE, y * SIZE);
			if(game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor_ptr, x * SIZE, y * SIZE);
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->collect_ptr, x * SIZE, y * SIZE);
			if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_ptr, x * SIZE, y * SIZE);
			if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player_ptr, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_struct so_long;

	ft_memset(&so_long, 0, sizeof(so_long));
	read_map(&so_long);
	copy_map(&so_long);
	check_map(&so_long);
	// int i = 0;
	// while(so_long.map_copy[i])
	// {
	// 	printf("line %d = %s", i, so_long.map_copy[i]);
	// 	i++;
	// }
	// i = 0;
	// printf("\ny = %d\n", so_long.player_y);
	// printf("x = %d\n", so_long.player_x);
	//flood_fill(&so_long, so_long.player_y, so_long.player_y);
	// while (so_long.map_copy[i])
	// {	
	// 	printf("line %d = %s", i, so_long.map_copy[i]);
	// 	i++;
	// }
	so_long.mlx_ptr = mlx_init();
	if(!so_long.mlx_ptr)
		return(1);
	so_long.win_ptr = mlx_new_window(so_long.mlx_ptr, 
					so_long.map_width * SIZE, 
					so_long.map_height * SIZE, "SO_LONG");
	printf("\n---------end----------\n");
	if (!so_long.win_ptr)
		return(free(so_long.mlx_ptr), 1);
	set_images(&so_long);
	place_images(&so_long);
	//mlx_put_image_to_window(so_long.mlx_ptr, so_long.win_ptr, so_long.wall_ptr, 0, 0);
	mlx_hook(so_long.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &so_long);
	mlx_hook(so_long.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &so_long);
	mlx_loop(so_long.mlx_ptr);
	return (0);

}