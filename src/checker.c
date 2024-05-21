/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:28:06 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/21 18:19:13 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_walls(t_struct *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		if (y == 0 || y == game->map_height - 1)
		{
			while (x < game->map_width)
			{
				if (game->map[y][x] != '1')
					return (print_string("Wrong walls\n") & 0);
				x++;
			}
		}
		else if (game->map[y][0] != '1'
			|| game->map[y][game->map_width - 1] != '1')
			return (print_string("Wrong wall\n") & 0);
		y++;
	}
	return (1);
}

int	check_exit(t_struct *game)
{
	int	y;
	int	x;

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
		printf("Wrong number of exits\n");
		return (0);
	}
	return (1);
}

int	check_colective(t_struct *game)
{
	int	y;
	int	x;

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
		printf("No collective\n");
		return (0);
	}
	return (1);
}

int	check_player(t_struct *game)
{
	int	y;
	int	x;

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
		return (printf("Wrong player count\n") && 0);
	game->count_player = 0;
	return (1);
}

int	check_char(t_struct *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '1' &&
				game->map[y][x] != '0' &&
				game->map[y][x] != 'P' &&
				game->map[y][x] != 'C' &&
				game->map[y][x] != 'E' &&
				game->map[y][x] != '\n')
			{
				printf("Wrong char on the map\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
