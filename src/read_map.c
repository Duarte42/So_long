/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:12:02 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/21 19:29:42 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	strlen_helper(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	return (i);
}

int	read_map(t_struct *game, char *map)
{
	char	*str;

	game->fd = open(map, O_RDONLY, 0);
	game->map_height = 0;
	str = get_next_line(game->fd);
	if (!str)
		return (print_string("No map\n") * 0);
	game->map_width = strlen_helper(str);
	while (str)
	{
		free(str);
		str = get_next_line(game->fd);
		if (str && game->map_width != strlen_helper(str))
		{
			free(str);
			print_string("Map is not retangle\n");
			close(game->fd);
			return (0);
		}
		game->map_height++;
	}
	close(game->fd);
	free(str);
	return (1);
}
