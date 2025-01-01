/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mole_pc <mole_pc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:12:06 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/01 12:14:36 by mole_pc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
int	color_erorr(char *str)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			cont++;
		i++;
	}
	if (cont > 2)
	{
		print_error("too many commas");
		return (1);
	}
	return (0);
}

int	in_color_range(color_t *color_)
{
	if ((color_->r < 0 || color_->r > 255) || (color_->g < 0 || color_->g > 255)
		|| (color_->b < 0 || color_->b > 255))
	{
		print_error("color values should be between 0 and 255\n");
		return (1);
	}
	return (0);
}
