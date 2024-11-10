/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:28:24 by wait-bab          #+#    #+#             */
/*   Updated: 2024/03/16 13:51:59 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *str)
{
	char	*buffer;
	ssize_t	c;

	c = 1;
	buffer = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (buffer == NULL)
		return (NULL);
	while (c != 0)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c < 0)
			return (free(str), free(buffer), NULL);
		buffer[c] = '\0';
		str = join(str, buffer);
		if ((does_char(buffer, '\n')) == 1)
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*rt_line;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (line == NULL)
		return (NULL);
	rt_line = new_line(line);
	line = backup(line);
	return (rt_line);
}
