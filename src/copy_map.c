/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:42:43 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/10 13:39:38 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	dup_map(t_struct *game, char *map)
{
	int	i;

	i = 0;
	game->fd = open(map, O_RDONLY, 0);
	game->map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map_copy)
	{
		printf("fail to allocate for the map_copy\n");
		return (0);
	}
	while (i < game->map_height)
	{
		game->map_copy[i] = get_next_line(game->fd);
		i++;
	}
	game->map_copy[i] = NULL;
	close(game->fd);
	return (1);
}

int	copy_map(t_struct *game, char *map)
{
	int	i;

	i = 0;
	game->fd = open(map, O_RDONLY, 0);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
	{
		printf("fail to allocate for the map\n");
		return (0);
	}
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(game->fd);
		i++;
	}
	game->map[i] = NULL;
	(void)dup_map(game, map);
	close(game->fd);
	return (1);
}
