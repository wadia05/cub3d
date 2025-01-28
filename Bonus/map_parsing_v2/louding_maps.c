/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louding_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:19 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:56:24 by wait-bab         ###   ########.fr       */
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

t_map_list	*create_map_list(char *map, tracker_t **free_head)
{
	t_map_list	*new;

	new = tracker_malloc(sizeof(t_map_list), free_head);
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

t_map_list	*add_map_list(t_map_list *head, char *map, t_map *stc)
{
	t_map_list	*new;
	t_map_list	*tmp;

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
