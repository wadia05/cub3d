/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mole_pc <mole_pc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:33 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/20 07:50:37 by mole_pc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_char_here(const char *line, const char *chars)
{
	while (*line)
	{
		if (ft_strchr(chars, *line))
		{
			return (true);
		}
		line++;
	}
	return (false);
}

void	trim_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

void	remove_newline(char *line)
{
	char	*newline;

	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
}

int	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	close_file(int file)
{
	char	*line;

	line = get_next_line(file);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(file);
	}
	close(file);
}
