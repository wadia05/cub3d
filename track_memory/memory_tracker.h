/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tracker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:54 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:47:23 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_TRACKER_H
# define MEMORY_TRACKER_H

# include "../libft_42/libft.h"
# include <stdlib.h>

typedef struct tracker_s
{
	void				*address;
	struct tracker_s	*next_addr;
}						tracker_t;

void					*tracker_malloc(size_t size, tracker_t **hd_tracker);
void					free_all_allocate(tracker_t **hd_tracker);

#endif