/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:33 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 13:00:38 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3d.h"

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

int	handle_texture(char **dest, char *path, char *type, map_t *stc)
{
	if (*dest != NULL)
		return (print_error("Duplicate texture definition"));
	if (validate_texture_path(path, type) != 0)
		return (1);
	*dest = ft_strdup_v2(path, stc->free_head);
	if (!*dest)
		return (print_error("Memory allocation failed"));
	return (0);
}

map_t	*init_map_structure(tracker_t *free_hd)
{
	map_t	*stc;

	stc = tracker_malloc(sizeof(map_t), &free_hd);
	if (!stc)
		return (NULL);
	ft_memset(stc, 0, sizeof(map_t));
	stc->f_color = tracker_malloc(sizeof(color_t), &free_hd);
	stc->c_color = tracker_malloc(sizeof(color_t), &free_hd);
	if (!stc->f_color || !stc->c_color)
	{
		free_all_allocate(&free_hd);
		return (NULL);
	}
	ft_memset(stc->f_color, 0, sizeof(color_t));
	ft_memset(stc->c_color, 0, sizeof(color_t));
	return (stc);
}

int	parse_texture_line(map_t *stc, char **tokens)
{
	if (!tokens[1])
		return (print_error("Missing texture path"));
	if (word_count(tokens) > 2)
		print_error("more then one path");
	if (ft_strncmp(tokens[0], "NO", 3) == 0)
		return (handle_texture(&stc->no, tokens[1], "NO", stc));
	else if (ft_strncmp(tokens[0], "SO", 3) == 0)
		return (handle_texture(&stc->so, tokens[1], "SO", stc));
	else if (ft_strncmp(tokens[0], "WE", 3) == 0)
		return (handle_texture(&stc->we, tokens[1], "WE", stc));
	else if (ft_strncmp(tokens[0], "EA", 3) == 0)
		return (handle_texture(&stc->ea, tokens[1], "EA", stc));
	return (print_error("Unknown texture identifier"));
}

int	parse_color_line(map_t *stc, char **tokens, char *line)
{
	if (ft_strncmp(tokens[0], "F", 2) == 0 && line)
	{
		if (parse_color(line, stc->f_color) != 0)
			return (print_error("Invalid floor color format"));
	}
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && line)
	{
		if (parse_color(line, stc->c_color) != 0)
			return (print_error("Invalid ceiling color format"));
	}
	else
	{
		return (print_error("Invalid color identifier"));
	}
	return (0);
}

int	parse_line(map_t *stc, char *line)
{
	int		ret;
	char	**tokens;

	ret = 0;
	if (!stc || !line)
		return (print_error("NULL pointer in parse_line"));
	remove_newline(line);
	trim_end(line);
	if (line[0] == '\0' && line[1] == '\0' && stc->map_str == true)
	{
		write(1, "helooooo", 9);
		stc->map_data = add_map_list(stc->map_data, "\n", stc);
	}
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed"));
	if (tokens[0])
	{
		if (ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "SO",
				2) == 0 || ft_strncmp(tokens[0], "WE", 2) == 0
			|| ft_strncmp(tokens[0], "EA", 2) == 0)
		{
			if (stc->map_str == true)
				ret = print_error("Map is not at the end");
			else
				ret = parse_texture_line(stc, tokens);
		}
		else if (ft_strncmp(tokens[0], "F", 1) == 0 || ft_strncmp(tokens[0],
				"C", 1) == 0)
			ret = parse_color_line(stc, tokens, line);
		else if (is_char_here(line, "01WSEN"))
		{
			stc->map_str = true;
			if (!is_char_here(line, "01WSEN \t"))
				ret = print_error("Invalid character in map");
			else
				stc->map_data = add_map_list(stc->map_data, line, stc);
		}
		else
			ret = print_error("Invalid identifier");
	}
	free_split(tokens);
	return (ret);
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
