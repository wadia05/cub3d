/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:46 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 11:24:59 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3d.h"

int	validate_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t' || c == '\n');
}

int	check_border_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\t')
		{
			print_error("Error: Border lines must \
                contain only walls and spaces");
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_empty_lines(map_list_t **map_data)
{
	map_list_t	*tmp;
	map_list_t	*prev;

	tmp = *map_data;
	prev = NULL;
	while (tmp)
	{
		if (tmp->next && tmp->map[0] == '\n' && tmp->next->map[0] != '\n')
		{
			print_error("Error: Empty line detected in map");
			return (1);
		}
		if (tmp->map[0] == '\n')
		{
			if (prev)
				prev->next = NULL;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	validate_map_borders_and_walls(map_list_t *map_data, map_t *stc)
{
	map_list_t	*tmp;

	tmp = map_data;
	while (tmp)
	{
		if (!tmp->prev || !tmp->next || tmp->next->map[0] == '\n')
		{
			if (check_border_line(tmp->map))
				return (1);
		}
		else
		{
			if (tmp->map[tmp->ws] != '1')
			{
				print_error("First index not wall");
				return (1);
			}
			if (check_zero(tmp, stc))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parse_line_maps(map_t *stc)
{
	if (!stc || !stc->map_data)
		return (1);
	if (handle_empty_lines(&stc->map_data))
		return (1);
	if (validate_map_borders_and_walls(stc->map_data, stc))
		return (1);
	if (player_check(stc->map_data, stc) != 0)
		return (1);
	return (0);
}
