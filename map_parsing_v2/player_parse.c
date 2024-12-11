/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:24 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 09:29:05 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3d.h"

int	is_valid_alpha(char alpha)
{
	if (alpha == 'E' || alpha == 'S' || alpha == 'W' || alpha == 'N')
		return (0);
	else
	{
		print_error("alpha error not valid\n");
		return (1);
	}
}

int	find_player(map_list_t *ply)
{
	int	i;
	int	ply_offset;

	i = 0;
	ply_offset = 0;
	while (ply->map[i] != '\0')
	{
		if (ply->map[i] == '1' || ply->map[i] == '0' || ply->map[i] == ' '
			|| ply->map[i] == '\t')
		{
			i++;
			continue ;
		}
		if (ply->map[i] >= 'A' && ply->map[i] <= 'Z')
		{
			if (is_valid_alpha(ply->map[i]) != 0)
				free_at_exit();
			check_current_positions(ply, i);
			check_adjacent_positions(ply, i);
			ply_offset++;
		}
		else
		{
			print_error("player character wrong 'W E S N'\n");
			free_at_exit();
		}
		i++;
	}
	return (ply_offset);
}

int	player_check(map_list_t *hd)
{
	map_list_t	*tmp;
	int			ply_offset;

	tmp = hd;
	ply_offset = 0;
	while (tmp != NULL)
	{
		ply_offset += find_player(tmp);
		if (ply_offset > 1)
		{
			print_error("too many players in map");
			free_at_exit();
		}
		tmp = tmp->next;
	}
	if (ply_offset == 0)
	{
		print_error("no player in map\n");
		free_at_exit();
	}
	return (0);
}
