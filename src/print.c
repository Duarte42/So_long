/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:56:28 by duamarqu          #+#    #+#             */
/*   Updated: 2024/05/21 19:18:30 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	print_string(char *str)
{
	int	count;

	count = 0;
	write(1, "Error\n", 6);
	if (str == NULL)
		str = "(null)";
	while (*str)
		count += write(1, str++, 1);
	return (count);
}

void	print_step(int step)
{
	char	c;

	if (step == -2147483648)
		write(1, "-2147483648", 11);
	else if (step < 0)
	{
		write(1, "-", 1);
		print_step(-step);
	}
	else if (step > 9)
	{
		print_step(step / 10);
		print_step(step % 10);
	}
	else
	{
		c = step + 48;
		write(1, &c, 1);
	}
}
