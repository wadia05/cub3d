/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:34:08 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 18:12:05 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	validate_file_extension(char *ext)
{
	int	len;

	trim_end(ext);
	len = ft_strlen(ext);
	if (ext[len - 1] == 'b' && ext[len - 2] == 'u' && ext[len - 3] == 'c'
		&& ext[len - 4] == '.')
	{
		printf("good trip extension\n");
	}
	else
	{
		print_error("bad trip extension\n");
		exit(1);
	}
	return (0);
}

int	word_count(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	printf("%d\n", i);
	return (i);
}

char	*ft_strdup_v2(const char *s1, t_tracker **free_head)
{
	char	*str;
	int		i;

	i = 0;
	str = tracker_malloc(ft_strlen(s1) * sizeof(char) + 1, free_head);
	if (str == NULL)
		return (NULL);
	while (*(s1 + i))
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*ft_strjoin_v2(char const *s1, char const *s2, t_tracker **free_head)
{
	char	*aloo;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_v2(s2, free_head));
	if (!s2)
		return (ft_strdup_v2(s1, free_head));
	aloo = tracker_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, free_head);
	if (aloo == NULL)
		return (NULL);
	ft_strlcpy(aloo, s1, ft_strlen(s1) + 1);
	ft_strlcat(aloo, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (aloo);
}
