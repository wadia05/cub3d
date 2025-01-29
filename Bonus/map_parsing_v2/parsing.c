/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:58 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 12:29:54 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_Bonus.h"

int	parse_color_line(t_map *stc, char **tokens, char *line)
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

static int	parse_identifier(t_map *stc, char **tokens, char *line)
{
	if (ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "SO",
			2) == 0 || ft_strncmp(tokens[0], "WE", 2) == 0
		|| ft_strncmp(tokens[0], "EA", 2) == 0)
	{
		if (stc->map_str == true)
			return (print_error("Map is not at the end"));
		return (parse_texture_line(stc, tokens));
	}
	else if (ft_strncmp(tokens[0], "F", 1) == 0 || ft_strncmp(tokens[0], "C",
			1) == 0)
	{
		if (stc->map_str == true)
			return (print_error("coloe in inside map"));
		return (parse_color_line(stc, tokens, line));
	}
	return (-1);
}

static int	parse_map_line(t_map *stc, char *line)
{
	if (is_char_here(line, "013WSEN"))
	{
		stc->map_str = true;
		if (!is_char_here(line, "013WSEN \t"))
			return (print_error("Invalid character in map"));
		stc->map_data = add_map_list(stc->map_data, line, stc);
		return (0);
	}
	return (print_error("Invalid identifier"));
}

int	parse_line(t_map *stc, char *line)
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
		stc->map_data = add_map_list(stc->map_data, "\n", stc);
		return (0);
	}
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed"));
	if (tokens[0])
	{
		ret = parse_identifier(stc, tokens, line);
		if (ret == -1)
			ret = parse_map_line(stc, line);
	}
	free_split(tokens);
	return (ret);
}
