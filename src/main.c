
#include "../include/so_long.h"

void ft_error(char *str)
{
	
}

void is_collectable(t_struct *data, int y, int x)
{


	if(data->map[y][x] == 'C')
	{
		data->map[y][x] = '0';
		data->temp_collect += 1;
		//printf("collectable count --> %d\n", data->temp_collect);
	}
	if(data->map[y][x] == 'E')
	{
		if(data->temp_collect == data->count_collect)
		{
			//printf("podes sair\n");
			on_destroy(data);
		}
		//else
			//printf("ainda nao podes\n");
			//exit(0);
	}
	if (data->player_y != y || data->player_x != x)
	{
		data->count_player++;
		printf("%d\n", data->count_player);
	}
}

int on_keypress(int keysym, t_struct *data)
{
	int y;
	int x;

	y = data->player_y;
	x = data->player_x;
	if (data->map[y][x] != 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_ptr, x * SIZE, y * SIZE);
	if (keysym == KEY_W && data->map[y - 1][x] != '1')
		data->player_y -= 1;
	else if (keysym == KEY_S && data->map[y+1][x] != '1')
		data->player_y += 1;
	else if (keysym == KEY_A && data->map[y][x-1] != '1')
		data->player_x -= 1;
	else if (keysym == KEY_D && data->map[y][x+1] != '1')
		data->player_x += 1;
	else if (keysym == KEY_ESC)
		on_destroy(data);
	is_collectable(data, y, x);
	if (data->map[data->player_y][data->player_x] != 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_ptr, data->player_x * SIZE, data->player_y * SIZE);
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

	// printf("y =%d\n", y);
	// printf("x =%d\n", x);
	if(game->map_copy[y][x] == '1')
		return (0);
	else if (game->map_copy[y][x] == 'E')
		game->temp_exit++;
	else if (game->map_copy[y][x] == 'C')
		game->temp_collect++;
	game->map_copy[y][x] = '1';
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

	w = SIZE;
	h = SIZE;

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

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void check_args(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc != 2)
	{
		printf("too few arguments\n");
		exit(0);

	}	
	
	while (argv[1][i])
		i++;
	i -= 4;
	if (ft_strcmp(&argv[1][i], ".ber"))
	{
		printf("wrong map file \n");
		exit(0);
	}	
		
}
int	main(int argc, char **argv)
{
	t_struct so_long;

	check_args(argc, argv);

	ft_memset(&so_long, 0, sizeof(so_long));
	if(!read_map(&so_long, argv[1]) ||
		!copy_map(&so_long, argv[1]) ||
		!check_map(&so_long))
		return(printf("Error\n") && &on_destroy && 0);
	so_long.mlx_ptr = mlx_init();
	if(!so_long.mlx_ptr)
		return(1);
	so_long.win_ptr = mlx_new_window(so_long.mlx_ptr, 
					so_long.map_width * SIZE, 
					so_long.map_height * SIZE, "so_long");
	if (!so_long.win_ptr)
		return(free(so_long.mlx_ptr), 1);
	set_images(&so_long);
	place_images(&so_long);;
	mlx_hook(so_long.win_ptr, KeyRelease, KeyReleaseMask, on_keypress, &so_long);
	mlx_hook(so_long.win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, &so_long);
	mlx_loop(so_long.mlx_ptr);
	return (0);

}

