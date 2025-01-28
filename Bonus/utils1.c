/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:49:13 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/28 17:55:27 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_cub3d *cub)
{
	int	i;

	i = 0;
	if (!(cub->map))
		return ;
	while (i < cub->map_y)
	{
		if (cub->map[i])
			free(cub->map[i]);
		i++;
	}
	free(cub->map);
	free(cub->ray);
	free(cub);
}

double	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	check_mov(int x, int y, t_cub3d *cub)
{
	int	i;
	int	j;
	int	map_row;
	int	map_col;

	i = -BUFFER;
	while (i < (PLAYER_SIZE + BUFFER))
	{
		j = -BUFFER;
		while (j < (PLAYER_SIZE + BUFFER))
		{
			map_row = (y + i) / cub->map_unit;
			map_col = (x + j) / cub->map_unit;
			if (map_row >= 0 && map_row < cub->map_y && map_col >= 0
				&& map_col < cub->map_x)
			{
				if (cub->map[map_row][map_col] == '1'
					|| cub->map[map_row][map_col] == '3')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_ray_v2(t_ray *ray)
{
	ray->distv = 0;
	ray->dist = 0;
	ray->yh_was_adoor = 0;
	ray->xv_was_adoor = 0;
	ray->yv_was_adoor = 0;
	ray->x_was_adoor = 0;
	ray->y_was_adoor = 0;
	ray->xV = 0;
	ray->yV = 0;
	ray->is_hori = 0;
	ray->is_door_h = 0;
	ray->is_door_v = 0;
	ray->is_door_close_h = 0;
	ray->is_door_close_v = 0;
	ray->is_door_close = 0;
	ray->dist_door = 0;
	ray->is_door = 0;
}

int	init_ray(t_cub3d *cub)
{
	int	i;

	free(cub->ray);
	cub->ray = malloc(sizeof(t_ray) * cub->num_rays);
	if (cub->ray == NULL)
		return (1);
	i = 0;
	while (i < cub->num_rays)
	{
		init_ray_v2(&cub->ray[i]);
		i++;
	}
	return (0);
}
