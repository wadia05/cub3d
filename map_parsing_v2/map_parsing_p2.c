/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:23:55 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 12:19:30 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3d.h"

void	check_current_positions(map_list_t *tmp, int i, map_t *stc)
{
	if (!tmp || !tmp->map)
		return ;
	if (tmp->map[i + 1] == ' ' || tmp->map[i - 1] == ' ' || !tmp->map[i + 1])
	{
		print_error("Error: Map boundary validation failed \
			- invalid wall configuration");
		free_at_exit(stc);
	}
	if (!tmp->next || tmp->next->length <= i)
	{
		print_error("Error: Map boundary validation failed \
			- invalid map dimensions");
		free_at_exit(stc);
	}
}

void	check_adjacent_positions(map_list_t *tmp, int i, map_t *stc)
{
	if (!tmp || !tmp->prev || !tmp->next || !tmp->prev->map || !tmp->next->map)
		return ;
	if (tmp->prev->map[i] == ' ' || tmp->prev->map[i] == '\t'
		|| !tmp->prev->map[i])
	{
		print_error("Error: Invalid map - open boundary detected above");
		free_at_exit(stc);
	}
	if (tmp->next->map[i] == ' ' || tmp->next->map[i] == '\t'
		|| !tmp->next->map[i])
	{
		print_error("Error: Invalid map - open boundary detected below");
		free_at_exit(stc);
	}
}

int	check_zero(map_list_t *tmp, map_t *stc)
{
	int i;

	i = 0;
	if (!tmp || !tmp->map)
		return (1);
	while (tmp->map[i])
	{
		if (ft_isdigit(tmp->map[i]) && tmp->map[i] != '1' && tmp->map[i] != '0')
		{
			print_error("Error: Invalid character in map");
			free_at_exit(stc);
		}
		if (i == 0 && (tmp->map[i] == '0' || tmp->map[tmp->length - 1] != '1'))
		{
			print_error("Error: Map must be enclosed by walls");
			free_at_exit(stc);
		}
		if (tmp->map[i] == '0')
		{
			check_current_positions(tmp, i, stc);
			check_adjacent_positions(tmp, i, stc);
		}
		i++;
	}
	return (0);
}
