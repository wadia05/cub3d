/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:34:03 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:56:24 by wait-bab         ###   ########.fr       */
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

int	validate_player_character(char player_char, t_map *stc)
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

int	find_player(t_map_list *ply, t_map *stc)
{
	int	i;
	int	ply_offset;

	i = 0;
	ply_offset = 0;
	while (ply->map[i] != '\0')
	{
		if (ply->map[i] == '1' || ply->map[i] == '0' || ply->map[i] == ' '
			|| ply->map[i] == '\t' || ply->map[i] == '3')
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

int	player_check(t_map_list *hd, t_map *stc)
{
	t_map_list	*tmp;
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
