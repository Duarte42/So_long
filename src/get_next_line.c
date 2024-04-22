/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:15:45 by duamarqu          #+#    #+#             */
/*   Updated: 2024/04/17 17:23:55 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_line;
	int			bytes;

	bytes = 0;
	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		while (buffer[bytes])
			buffer[bytes] = '\0';
		return (NULL);
	}
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		new_line = ft_strjoin(new_line, buffer);
		if (ft_nlhandle(buffer) == 1)
			break ;
	}
	return (new_line);
}
/*
int	main(void)
{
	char	*texto;
	int		fd;

	fd = open("text.txt", O_RDONLY, 0);
	while(1)
	{
		texto = get_next_line(fd);
		if (!texto)
			break ;
		printf("%s\n", texto);
		free(texto);
	}
	close (fd);
	return (0);
}*/