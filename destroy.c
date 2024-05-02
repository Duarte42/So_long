#include "../include/so_long.h"

void freemap(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void on_destroy(t_struct *data)
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