#include "../include/so_long.h"

int check_walls(t_struct *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		if (y == 0 || y == game->map_height - 1)
		{
			while (x < game->map_width)
			{
				if (game->map[y][x] != 'I')
				{
					printf("Deu bosta nas Walls\n");
					return (0);
				}
				x++;
			}
		}
		else
		{
			if (game->map[y][0] != 'I' || game->map[y][game->map_width - 1] != 'I')
			{
				printf("Deu bosta nas Walls\n");
				return (0);
			}
		}
		y++;
	}
	return (1);
}
int check_exit(t_struct *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'E')
				game->count_exit++;
			x++;
		}
		y++;
	}
	if (game->count_exit != 1)
	{
		printf("The number of exit is wrong!\n");
		return (0);
	}
	return (1);
}

int check_colective(t_struct *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->count_collect++;
			x++;
		}
		y++;
	}
	if (game->count_collect < 1)
	{
		printf("The number of collectables is wrong!\n");
		return (0);
	}
	return (1);
}

int check_player(t_struct *game)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				game->count_player++;
			}
			x++;
		}
		y++;
	}
	if (game->count_player != 1)
		return (0);
	return (1);
}

int check_map(t_struct *game)
{
	check_walls(game);
	check_exit(game);
	check_colective(game);
	check_player(game);
	return (1);
}