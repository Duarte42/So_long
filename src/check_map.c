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
				if (game->map[y][x] != '1')
				{
					//printf("Error\n");
					return (0);
				}
				x++;
			}
		}
		else
		{
			if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
			{
				//printf("Error\n");
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
		//printf("Error\n");
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
		//printf("Error\n");
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
		return (printf("Error\n") && 0);
	game->count_player = 0;
	return (1);
}

void free_maps(t_struct *game)
{
	int i;

	i = 0;
	while(game->map[i] && game->map_copy[i])
	{
		free(game->map[i]);
		free(game->map_copy[i]);
		i++;

	}	
	free(game->map);
	free(game->map_copy);

}

int check_map(t_struct *game)
{
	if (!check_player(game) ||
	!check_walls(game) ||
	!check_exit(game) ||
	!check_colective(game))
	{
		free_maps(game);
		return (0);
	}
	flood_fill(game, game->player_y, game->player_x);
	if(game->count_collect != game->temp_collect ||
		game->count_exit != game->temp_exit)
		{
			free_maps(game);
			return(0);
		}
	game->temp_collect = 0;
	return (1);
}