// #include <mlx.h>
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
int	main(void)
{
	t_struct so_long;

	ft_memset(&so_long, 0, sizeof(so_long));
	read_map(&so_long);
	copy_map(&so_long);
	check_map(&so_long);
	int i = 0;
	while(so_long.map_copy[i])
	{
		printf("line %d = %s", i, so_long.map_copy[i]);
		i++;
	}
	i = 0;
	printf("\ny = %d\n", so_long.player_y);
	printf("x = %d\n", so_long.player_x);
	flood_fill(&so_long, so_long.player_y, so_long.player_y);
	while (so_long.map_copy[i])
	{
		printf("line %d = %s", i, so_long.map_copy[i]);
		i++;
	}
	printf("\n---------end----------\n");
	return (0);

}