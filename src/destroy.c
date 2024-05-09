/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:57:41 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/09 11:58:08 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	freemap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_maps(t_struct *game)
{
	int	i;

	i = 0;
	while (game->map[i] && game->map_copy[i])
	{
		free(game->map[i]);
		free(game->map_copy[i]);
		i++;
	}
	free(game->map);
	free(game->map_copy);
}

int	on_destroy(t_struct *data)
{
	mlx_destroy_image(data->mlx_ptr, data->floor_ptr);
	mlx_destroy_image(data->mlx_ptr, data->wall_ptr);
	mlx_destroy_image(data->mlx_ptr, data->collect_ptr);
	mlx_destroy_image(data->mlx_ptr, data->player_ptr);
	mlx_destroy_image(data->mlx_ptr, data->exit_ptr);
	freemap(data->map);
	freemap(data->map_copy);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
