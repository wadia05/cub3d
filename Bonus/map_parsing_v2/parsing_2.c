/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:46 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 20:27:57 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_Bonus.h"

int	handle_texture(char **dest, char *path, char *type, t_map *stc)
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

t_map	*init_map_structure(t_tracker **free_hd)
{
	t_map	*stc;

	stc = tracker_malloc(sizeof(t_map), free_hd);
	if (!stc)
		return (NULL);
	ft_memset(stc, 0, sizeof(t_map));
	stc->f_color = tracker_malloc(sizeof(t_color), free_hd);
	stc->c_color = tracker_malloc(sizeof(t_color), free_hd);
	if (!stc->f_color || !stc->c_color)
	{
		free_all_allocate(free_hd);
		return (NULL);
	}
	ft_memset(stc->f_color, 0, sizeof(t_color));
	ft_memset(stc->c_color, 0, sizeof(t_color));
	return (stc);
}

int	parse_texture_line(t_map *stc, char **tokens)
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

int	process_map_file(t_map *stc, char *filename, t_tracker **free_head)
{
	int		file;
	char	*line;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		free_all_allocate(free_head);
		return (print_error("Cannot open map file"));
	}
	line = get_next_line(file);
	while (line != NULL)
	{
		if (parse_line(stc, line))
		{
			free(line);
			close_file(file);
			free_all_allocate(free_head);
			return (1);
		}
		free(line);
		line = get_next_line(file);
	}
	close_file(file);
	return (0);
}
