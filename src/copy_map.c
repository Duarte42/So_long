#include "../include/so_long.h"

int dup_map(t_struct *game)
{
    int y;
    int x;

    y = 0;
    x = 0;
    game->map_copy = malloc(sizeof(char *) * game->map_height);
    while (game->map[y])
    {
        game->map_copy[y] = malloc(sizeof(char) * game->map_width);
        while (game->map[y][x])
        {
            game->map_copy[y][x] = game->map[y][x];
            x++;
        }
        game->map_copy[y][x] = 0;
        x = 0;
        y++;
    }
    game->map_copy[y] = NULL;
    return (1);
}

int copy_map(t_struct *game)
{
    int i;

    i = 0;
    game->fd = open("map.ber", O_RDONLY, 0);
    game->map = malloc(sizeof(char *) * game->map_height);
   // game->fd = open("map.txt", O_RDONLY, 0);
    while (i < game->map_height)
    {

        game->map[i] = get_next_line(game->fd);
        //  printf("game.map[%d] = %s", i, game->map[i]);
        //---------   
        i++;
    }
    game->map[i] = NULL;
    dup_map(game);
    close(game->fd);
    return (1);
}