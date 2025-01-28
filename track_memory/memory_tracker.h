/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tracker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:54 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 18:12:05 by wait-bab         ###   ########.fr       */
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
}						t_tracker;

void					*tracker_malloc(size_t size, t_tracker **hd_tracker);
void					free_all_allocate(t_tracker **hd_tracker);

#endif