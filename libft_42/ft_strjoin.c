/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:59 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 10:14:45 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_v2(char const *s1, char const *s2, tracker_t *free_head)
{
	char	*aloo;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	aloo = tracker_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, &free_head);
	if (aloo == NULL)
		return (NULL);
	ft_strlcpy(aloo, s1, ft_strlen(s1) + 1);
	ft_strlcat(aloo, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (aloo);
}
