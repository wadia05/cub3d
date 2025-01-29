/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:46:12 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 21:11:40 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_horizontal_ray(t_cub3d *cub, double start_angle, t_ray *rays)
{
	rays->dof = 0;
	rays->atan = -1.0 / tan(start_angle);
	if (start_angle > PI)
	{
		rays->yh = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.0004;
		rays->xh = (cub->y - rays->yh) * rays->atan + cub->x;
		rays->yo = -cub->map_unit;
		rays->xo = -rays->yo * rays->atan;
	}
	else if (start_angle < PI)
	{
		rays->yh = ((int)(cub->y / cub->map_unit)) * cub->map_unit
			+ cub->map_unit;
		rays->xh = (cub->y - rays->yh) * rays->atan + cub->x;
		rays->yo = cub->map_unit;
		rays->xo = -rays->yo * rays->atan;
	}
	else
	{
		rays->xh = cub->x;
		rays->yh = cub->y;
		rays->dof = cub->ray_dof_max;
	}
	itirate_horizontal(rays, cub);
}

void	handle_vertical_ray(t_cub3d *cub, double start_angle, t_ray *rays)
{
	rays->dof = 0;
	rays->atan = -tan(start_angle);
	if (start_angle > PI / 2 && start_angle < 3 * PI / 2)
	{
		rays->xv = (floor(cub->x / cub->map_unit)) * cub->map_unit - 0.0004;
		rays->yv = (cub->x - rays->xv) * rays->atan + cub->y;
		rays->xo = -cub->map_unit;
		rays->yo = -rays->xo * rays->atan;
	}
	else if (start_angle < PI / 2 || start_angle > 3 * PI / 2)
	{
		rays->xv = (floor(cub->x / cub->map_unit)) * cub->map_unit
			+ cub->map_unit;
		rays->yv = (cub->x - rays->xv) * rays->atan + cub->y;
		rays->xo = cub->map_unit;
		rays->yo = -rays->xo * rays->atan;
	}
	else
	{
		rays->xv = cub->x;
		rays->yv = cub->y;
		rays->dof = cub->ray_dof_max;
	}
	itirate_vertical(rays, cub);
}

void	draw_ray_v2(t_cub3d *cub, t_ray *rays, double disth)
{
	(void)cub;
	rays->rx = rays->xh;
	rays->ry = rays->yh;
	rays->dist = disth;
	rays->is_hori = 0;
}

void	draw_ray(t_cub3d *cub, t_ray *rays)
{
	double	disth;
	double	distv;

	disth = dist(cub->x, cub->y, rays->xh, rays->yh);
	distv = dist(cub->x, cub->y, rays->xv, rays->yv);
	// rays->is_door_close = 0;
	if (disth < distv)
		draw_ray_v2(cub, rays, disth);
	else
	{
		rays->rx = rays->xv;
		rays->ry = rays->yv;
		rays->dist = distv;
		rays->is_hori = 1;
	}
}
