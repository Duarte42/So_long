#include "../include/so_long.h"

static int strlen_helper(const char *s1)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] != '\n')
        i++;
    return (i);
}

// char *ft_strjoin_2(char const *s1, char const *s2)
// {
//     char *s3;
//     int i;
//     int k;

//     i = 0;
//     k = 0;
//     s3 = malloc(strlen_helper(s1) + strlen_helper(s2) + 1);
//     if (s3 == NULL)
//         return (NULL);
//     while (s1[i])
//     {
//         s3[i] = s1[i];
//         i++;
//     }
//     while (s2[k])
//     {
//         s3[i++] = s2[k++];
//     }
//     s3[i] = '\0';
//     return (s3);
// }

int read_map(t_struct *game)
{
    char *str;
    int str_len;

    game->fd = open("map.ber", O_RDONLY, 0);
    game->map_height = 0;
    str = get_next_line(game->fd);
    str_len = strlen_helper(str);
    while (str)
    {
        free(str);
        str = get_next_line(game->fd);
        if (str && str_len != strlen_helper(str))
        {
            free(str);
            printf("NOT A RETANGLE!\n");
            close(game->fd);
            return (0);
        }
        game->map_height++;
    }
    game->map_width = str_len;
    close(game->fd);
    free(str);
    return (1);
}
