/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:24:20 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/21 18:12:14 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	is_collectable(t_struct *data, int y, int x)
{
	if (data->map[y][x] == 'C')
	{
		data->map[y][x] = '0';
		data->temp_collect += 1;
	}
	if (data->map[y][x] == 'E')
	{
		if (data->temp_collect == data->count_collect)
			on_destroy(data);
	}
	if (data->player_y != y || data->player_x != x)
	{
		data->count_player++;
		print_step(data->count_player);
		write(1, "\n", 1);
	}
}

void	set_images(t_struct *game)
{
	int	w;
	int	h;

	w = SIZE;
	h = SIZE;
	game->floor_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"./image/floor.xpm", &w, &h);
	game->wall_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"./image/wall.xpm", &w, &h);
	game->collect_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"./image/collective.xpm", &w, &h);
	game->player_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"./image/player.xpm", &w, &h);
	game->exit_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"./image/exit.xpm", &w, &h);
}

int	on_keypress(int keysym, t_struct *data)
{
	int	y;
	int	x;

	y = data->player_y;
	x = data->player_x;
	if (data->map[y][x] != 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor_ptr, x * SIZE, y * SIZE);
	if (keysym == KEY_W && data->map[y - 1][x] != '1')
		data->player_y -= 1;
	else if (keysym == KEY_S && data->map[y + 1][x] != '1')
		data->player_y += 1;
	else if (keysym == KEY_A && data->map[y][x - 1] != '1')
		data->player_x -= 1;
	else if (keysym == KEY_D && data->map[y][x + 1] != '1')
		data->player_x += 1;
	else if (keysym == KEY_ESC)
		on_destroy(data);
	is_collectable(data, y, x);
	if (data->map[data->player_y][data->player_x] != 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player_ptr, data->player_x * SIZE, data->player_y * SIZE);
	return (0);
}

void	place_pec(t_struct *game, int y, int x)
{
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->player_ptr, x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->exit_ptr, x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->collect_ptr, x * SIZE, y * SIZE);
}

void	place_images(t_struct *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->wall_ptr, x * SIZE, y * SIZE);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->floor_ptr, x * SIZE, y * SIZE);
			else
				place_pec(game, y, x);
			x++;
		}
		y++;
	}
}
