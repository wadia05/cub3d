/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:39:20 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:40:56 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	s_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	does_char(char *st, int k)
{
	int	i;

	if (st == NULL)
		return (0);
	i = 0;
	while (st[i])
	{
		if (st[i] == k)
			return (1);
		i++;
	}
	return (0);
}

char	*join(char *s_line, char *s_buff)
{
	int		i;
	int		j;
	char	*str;

	if (!s_line)
	{
		s_line = malloc(sizeof(char) * 1);
		s_line[0] = '\0';
	}
	str = malloc(s_len(s_line) + s_len(s_buff) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s_line[i] != '\0')
	{
		str[i] = s_line[i];
		i++;
	}
	j = 0;
	while (s_buff[j] != '\0')
		str[i++] = s_buff[j++];
	str[i] = '\0';
	free(s_line);
	return (str);
}

char	*new_line(char *line)
{
	char	*rn;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	if (line[0] == '\0')
		return (NULL);
	rn = malloc(sizeof(char) * (i + 1));
	if (!rn)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		rn[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		rn[i++] = '\n';
	rn[i] = '\0';
	return (rn);
}

char	*backup(char *str)
{
	int		i;
	int		k;
	char	*bk;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	bk = malloc((sizeof(char)) * s_len(str + i) + 1);
	if (bk == NULL)
		return (NULL);
	k = 0;
	while (str[i] != '\0')
		bk[k++] = str[i++];
	bk[k] = '\0';
	free(str);
	return (bk);
}
