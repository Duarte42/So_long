#include <mlx.h>
#include "window.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
int on_destroy(t_win *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
}
int on_keypress(int keysym, t_win *data)
{
    (void)data;
    printf("Pressed the key: %d\n", keysym);
    if (keysym == 65307) // EXIT KEY
        on_destroy(data);
    return (0);
}

int main(void)
{
    t_win data;

    void *image;
    char *relative_path = "./src/floor.xpm";
    int img_w = 50;
    int img_h = 50;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, img_w + 100, img_h + 100, "test window!");
    if (!data.win_ptr)
        return (free(data.mlx_ptr), 1);
    printf("%s\n", relative_path);
    image = mlx_xpm_file_to_image(data.mlx_ptr, relative_path, &img_w, &img_h);
    if (!image)
    {
        printf("Failed to load image\n");
        // return (free(data.mlx_ptr), 1);
    }
    // printf("THIS -> %d\n",
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, image, 0, 0);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, image, 50, 0);
    (void)image;
    printf("iiiihuhyherror\n");

    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
    mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}