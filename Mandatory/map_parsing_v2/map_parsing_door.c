/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_door.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:30 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:56:24 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_single_door_position(t_map_list *tmp, int i)
{
	if (tmp->map[i] == '3')
	{
		if (tmp->prev->map[i] == ' ' || tmp->prev->map[i] == '\t'
			|| !tmp->prev->map[i] || tmp->prev->length <= i
			|| tmp->next->length <= i)
		{
			print_error("Door is out");
			return (1);
		}
		if (tmp->map[i + 1] == ' ' || tmp->map[i - 1] == ' ' \
			|| tmp->map[i + 1] == '\t' || tmp->map[i - 1] == '\t')
			return (print_error("free space Door close"));
		if (tmp->map[i + 1] == '1' && tmp->map[i - 1] == '1'
			&& tmp->prev->map[i] != '1' && tmp->next->map[i] != '1')
			return (0);
		if (tmp->prev && tmp->next && tmp->prev->map[i] == '1'
			&& tmp->next->map[i] == '1' && tmp->map[i + 1] != '1' \
			&& tmp->map[i - 1] != '1')
			return (0);
		print_error("Door should be between two walls");
		exit(1);
	}
	return (0);
}

int	door_check(t_map_list *hd)
{
	t_map_list	*tmp;
	int			i;

	if (hd == NULL)
		return (1);
	tmp = hd;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->map[i] != '\0')
		{
			if (check_single_door_position(tmp, i) == 1)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
