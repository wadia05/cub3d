/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_copy2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:57:00 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/26 22:04:44 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_moraba3(int x, int y, int color, cub3d_t *cub)
{
	int	i;
	int	j;
	int	cube_size;

	i = 0;
	cube_size = cub->map_unit;
	while (i < cube_size)
	{
		j = 0;
		while (j < cube_size)
		{
			mlx_put_pixel(cub->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
	return (0);
}

void	deviate_ray_if_flanked(ray_t *rays, int num_rays)
{
	int	i;

	i = 1;
	while (i < num_rays - 1)
	{
		if (rays[i].is_hori == 1)
		{
			if (rays[i - 1].is_hori == 0 && rays[i + 1].is_hori == 0)
				rays[i].is_hori = 0;
		}
		else
		{
			if (rays[i - 1].is_hori == 1 && rays[i + 1].is_hori == 1)
				rays[i].is_hori = 1;
		}
		i++;
	}
}
double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	draw_wall2(cub3d_t *cub, ray_t *rays)
{
	float	start_angle;
	int		i;

	i = 0;
	deviate_ray_if_flanked(rays, cub->num_rays);
	start_angle = cub->angle - (PI / 6);
	while (i < cub->num_rays)
	{
		draw_wall(cub, &rays[i], i, start_angle);
		start_angle += DR;
		start_angle = normalize_angle(start_angle);
		i++;
	}
	return (0);
}

int	draw_rays(cub3d_t *cub)
{
	ray_t	*rays;
	float	start_angle;
	int		i;

	if (init_ray(cub))
		return (1);
	rays = cub->ray;
	start_angle = cub->angle - (PI / 6);
	i = 0;
	start_angle = normalize_angle(start_angle);
	while (i < cub->num_rays)
	{
		handle_horizontal_ray(cub, start_angle, &rays[i]);
		handle_vertical_ray(cub, start_angle, &rays[i]);
		draw_ray(cub, &rays[i]);
		start_angle += DR;
		start_angle = normalize_angle(start_angle);
		i++;
	}
	draw_wall2(cub, rays);
	return (0);
}
