/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:23 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:55:27 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_cub3d *cub, int ray_index)
{
	t_map		*txtur;
	int			y;
	uint32_t	ceiling_color;

	txtur = NULL;
	txtur = cub->info;
	y = -1;
	while (++y < txtur->wall_top)
	{
		if (cub->info->c_color)
			ceiling_color = (cub->info->c_color->r << 24) \
			| (cub->info->c_color->g << 16) \
			| (cub->info->c_color->b << 8) \
			| 0xFF;
		mlx_put_pixel(cub->img, ray_index, y, ceiling_color);
	}
}

void	render_floor(t_cub3d *cub, int ray_index)
{
	t_map		*txtur;
	uint32_t	floor_color;
	int			y;

	txtur = NULL;
	txtur = cub->info;
	floor_color = 0;
	y = txtur->wall_bottom + 1;
	while (y < HEIGHT)
	{
		if (cub->info->f_color)
		{
			floor_color = (cub->info->f_color->r << 24) \
			| (cub->info->f_color->g << 16) \
			| (cub->info->f_color->b << 8) \
			| 0xFF;
		}
		mlx_put_pixel(cub->img, ray_index, y, floor_color);
		y++;
	}
}
