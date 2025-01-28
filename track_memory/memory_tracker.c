/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tracker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:40 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:36:41 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_tracker.h"
#include <stdio.h>
#include <stdlib.h>

void	*tracker_malloc(size_t size, tracker_t **hd_tracker)
{
	void		*address_data;
	tracker_t	*node;

	address_data = malloc(size);
	if (address_data == NULL)
		return (NULL);
	node = malloc(sizeof(tracker_t));
	if (node == NULL)
	{
		free(address_data);
		return (NULL);
	}
	ft_memset(node, 0, sizeof(tracker_t));
	node->address = address_data;
	node->next_addr = *hd_tracker;
	*hd_tracker = node;
	return (address_data);
}

void	free_all_allocate(tracker_t **hd_tracker)
{
	tracker_t	*curr;
	tracker_t	*next;

	if (*hd_tracker == NULL)
		return ;
	curr = *hd_tracker;
	while (curr != NULL)
	{
		next = curr->next_addr;
		if (curr->address != NULL)
		{
			free(curr->address);
			curr->address = NULL;
		}
		free(curr);
		curr = next;
	}
	*hd_tracker = NULL;
}
