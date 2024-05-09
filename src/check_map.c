/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:38:48 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/09 14:57:12 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	flood_fill(t_struct *game, int y, int x)
{
	if (game->map_copy[y][x] == '1')
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

int	check_map(t_struct *game)
{
	if (!check_char(game)
		|| !check_player(game)
		|| !check_walls(game)
		|| !check_exit(game)
		|| !check_colective(game))
	{
		free_maps(game);
		return (0);
	}
	flood_fill(game, game->player_y, game->player_x);
	if (game->count_collect != game->temp_collect
		|| game->count_exit != game->temp_exit)
	{
		free_maps(game);
		return (0);
	}
	game->temp_collect = 0;
	return (1);
}
