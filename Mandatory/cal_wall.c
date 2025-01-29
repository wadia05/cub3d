/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:04 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 21:26:08 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loading_image(t_map *mp)
{
	mp->no_png = mlx_load_png(mp->no);
	if (!mp->no_png)
		return (1);
	mp->so_png = mlx_load_png(mp->so);
	if (!mp->so_png)
		return (1);
	mp->ea_png = mlx_load_png(mp->ea);
	if (!mp->ea_png)
		return (1);
	mp->we_png = mlx_load_png(mp->we);
	if (!mp->we_png)
		return (1);
	return (0);
}

mlx_texture_t	*get_texturte(t_cub3d *cub, t_ray *ray, double s_agl)
{
	if (!ray->is_hori)
	{
		if (s_agl > 0 && s_agl < PI)
			return (cub->info->so_png);
		else
			return (cub->info->no_png);
	}
	else
	{
		if (s_agl > PI / 2 && s_agl < 3 * PI / 2)
			return (cub->info->we_png);
		else
			return (cub->info->ea_png);
	}
	return (NULL);
}
