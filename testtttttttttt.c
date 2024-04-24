#include <mlx.h>
#include "include/window.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    // void *mlx_ptr;
    // void *win_ptr;

    // mlx_ptr = mlx_init();
    // if (!mlx_ptr)
    //     return (1);
    // win_ptr = mlx_new_window(mlx_ptr, 300, 300, "Hello World");
    // if (!win_ptr)
    //     return (2);
    // mlx_loop(mlx_ptr);

    t_win tutorial;

    tutorial = new_program(300, 300, "O NICO XUPA ROLA");
    if (!tutorial.mlx_ptr || !tutorial.win_ptr)
        return (1);
    t_img image_4x4;

    image_4x4.win = tutorial;
    image_4x4.img_ptr = mlx_new_image(tutorial.mlx_ptr, 4, 4);
    image_4x4.addr = mlx_get_data_addr(image_4x4.img_ptr, &(image_4x4.bpp), &(image_4x4.line_len), &(image_4x4.endian));
    image_4x4.w = 4;
    image_4x4.h = 4;
    printf("Let's Find out what's inside our structure :D\n");
    printf("img_ptr		: [%p]\n", image_4x4.img_ptr);
    printf("bpp		: [%d]\n", image_4x4.bpp);
    printf("line_len	: [%d]\n", image_4x4.line_len);
    printf("endian		: [%d]\n", image_4x4.endian);
    printf("addr		: [%p]\n", image_4x4.addr);

    // image = new_img(300, 300, tutorial);
    // memcpy(image.addr, "s4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vf", 16 * 4);
    // mlx_put_image_to_window(image.win.mlx_ptr, image.win.win_ptr, image.img_ptr, 10, 10);
    // mlx_destroy_image(tutorial.mlx_ptr, image.img_ptr);
    mlx_loop(tutorial.mlx_ptr);
    return (0);
}