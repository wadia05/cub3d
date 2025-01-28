/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:46:12 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 17:55:27 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_horizontal_ray(t_cub3d *cub, double start_angle, t_ray *rays)
{
	rays->dof = 0;
	rays->aTan = -1.0 / tan(start_angle);
	if (start_angle > PI)
	{
		rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.0004;
		rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
		rays->yo = -cub->map_unit;
		rays->xo = -rays->yo * rays->aTan;
	}
	else if (start_angle < PI)
	{
		rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit
			+ cub->map_unit;
		rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
		rays->yo = cub->map_unit;
		rays->xo = -rays->yo * rays->aTan;
	}
	else
	{
		rays->xH = cub->x;
		rays->yH = cub->y;
		rays->dof = cub->ray_dof_max;
	}
	itirate_horizontal(rays, cub);
}

void	handle_vertical_ray(t_cub3d *cub, double start_angle, t_ray *rays)
{
	rays->dof = 0;
	rays->aTan = -tan(start_angle);
	if (start_angle > PI / 2 && start_angle < 3 * PI / 2)
	{
		rays->xV = (floor(cub->x / cub->map_unit)) * cub->map_unit - 0.0004;
		rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;
		rays->xo = -cub->map_unit;
		rays->yo = -rays->xo * rays->aTan;
	}
	else if (start_angle < PI / 2 || start_angle > 3 * PI / 2)
	{
		rays->xV = (floor(cub->x / cub->map_unit)) * cub->map_unit
			+ cub->map_unit;
		rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;
		rays->xo = cub->map_unit;
		rays->yo = -rays->xo * rays->aTan;
	}
	else
	{
		rays->xV = cub->x;
		rays->yV = cub->y;
		rays->dof = cub->ray_dof_max;
	}
	itirate_vertical(rays, cub);
}

void	draw_ray_v2(t_cub3d *cub, t_ray *rays, double disth)
{
	rays->rx = rays->xH;
	rays->ry = rays->yH;
	rays->dist = disth;
	rays->is_hori = 0;
	rays->is_door = rays->is_door_h;
	rays->x_was_adoor = rays->xh_was_adoor;
	rays->y_was_adoor = rays->yh_was_adoor;
	rays->is_door_close = rays->is_door_close_h;
	rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor,
			rays->y_was_adoor);
}

void	draw_ray(t_cub3d *cub, t_ray *rays)
{
	double	disth;
	double	distv;

	disth = dist(cub->x, cub->y, rays->xH, rays->yH);
	distv = dist(cub->x, cub->y, rays->xV, rays->yV);
	rays->is_door_close = 0;
	if (disth < distv)
		draw_ray_v2(cub, rays, disth);
	else
	{
		rays->rx = rays->xV;
		rays->ry = rays->yV;
		rays->dist = distv;
		rays->is_hori = 1;
		rays->is_door = rays->is_door_v;
		rays->x_was_adoor = rays->xv_was_adoor;
		rays->y_was_adoor = rays->yv_was_adoor;
		rays->is_door_close = rays->is_door_close_v;
		rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor,
				rays->y_was_adoor);
	}
}
