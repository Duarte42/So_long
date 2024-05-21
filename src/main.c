/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:45:06 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/20 19:52:37 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*ft_memset(void *ptr, int ch, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)ptr;
	i = 0;
	while (i < n)
	{
		str[i] = ch;
		i++;
	}
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		print_string("wrong number of arguments\n");
		exit(0);
	}
	while (argv[1][i])
		i++;
	i -= 4;
	if (ft_strcmp(&argv[1][i], ".ber"))
	{
		print_string("wrong map file \n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_struct	so_long;

	check_args (argc, argv);
	ft_memset (&so_long, 0, sizeof(so_long));
	if (!read_map(&so_long, argv[1])
		|| !copy_map(&so_long, argv[1])
		|| !check_map(&so_long))
		return (&on_destroy && 0);
	so_long.mlx_ptr = mlx_init();
	if (!so_long.mlx_ptr)
		return (1);
	so_long.win_ptr = mlx_new_window(so_long.mlx_ptr, 
			so_long.map_width * SIZE, 
			so_long.map_height * SIZE, "so_long");
	if (!so_long.win_ptr)
		return (free(so_long.mlx_ptr), 1);
	set_images(&so_long);
	place_images(&so_long);
	mlx_hook(so_long.win_ptr, KeyRelease, KeyReleaseMask,
		on_keypress, &so_long);
	mlx_hook(so_long.win_ptr, DestroyNotify, StructureNotifyMask,
		on_destroy, &so_long);
	mlx_loop(so_long.mlx_ptr);
	return (0);
}
