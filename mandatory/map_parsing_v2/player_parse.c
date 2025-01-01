/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mole_pc <mole_pc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:24 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/01 11:51:27 by mole_pc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	validate_player_character(char player_char, map_t *stc)
{
	if (player_char >= 'A' && player_char <= 'Z')
	{
		if (is_valid_alpha(player_char) != 0)
		{
			free_at_exit(stc);
			return (0);
		}
		return (1);
	}
	print_error("player character wrong 'W E S N'\n");
	free_at_exit(stc);
	return (0);
}

int	find_player(map_list_t *ply, map_t *stc)
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
		if (validate_player_character(ply->map[i], stc))
		{
			check_current_positions(ply, i, stc);
			check_adjacent_positions(ply, i, stc);
			ply_offset++;
		}
		i++;
	}
	return (ply_offset);
}

int	player_check(map_list_t *hd, map_t *stc)
{
	map_list_t	*tmp;
	int			ply_offset;

	tmp = hd;
	ply_offset = 0;
	while (tmp != NULL)
	{
		ply_offset += find_player(tmp, stc);
		if (ply_offset > 1)
		{
			print_error("too many players in map");
			free_at_exit(stc);
		}
		tmp = tmp->next;
	}
	if (ply_offset == 0)
	{
		print_error("no player in map\n");
		free_at_exit(stc);
	}
	return (0);
}
