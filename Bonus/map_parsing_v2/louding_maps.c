/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louding_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:55 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/01 12:14:07 by wait-bab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	white_space(char *map)
{
	int	i;

	i = 0;
	while (map[i] == ' ' || map[i] == '\t')
		i++;
	return (i);
}

map_list_t	*create_map_list(char *map, tracker_t **free_head)
{
	map_list_t	*new;

	new = tracker_malloc(sizeof(map_list_t), free_head);
	if (new == NULL)
		return (NULL);
	trim_end(map);
	new->map = ft_strdup_v2(map, free_head);
	new->length = ft_strlen(map);
	new->ws = white_space(map);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

map_list_t	*add_map_list(map_list_t *head, char *map, map_t *stc)
{
	map_list_t	*new;
	map_list_t	*tmp;

	new = create_map_list(map, stc->free_head);
	if (new == NULL)
		return (NULL);
	if (head == NULL)
		return (new);
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (head);
}
