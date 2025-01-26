/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/228 16:15:21 by abenchel          #+#    #+#             */
/*   Updated: 2024/12/10 19:04:14 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_horizontal_ray(cub3d_t *cub, double start_angle, ray_t *rays)
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

void	handle_vertical_ray(cub3d_t *cub, double start_angle, ray_t *rays)
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

void	draw_ray_v2(cub3d_t *cub, ray_t *rays, double distH)
{
	rays->rx = rays->xH;
	rays->ry = rays->yH;
	rays->dist = distH;
	rays->is_hori = 0;
	rays->is_door = rays->is_door_h;
	rays->x_was_adoor = rays->xh_was_adoor;
	rays->y_was_adoor = rays->yh_was_adoor;
	rays->is_door_close = rays->is_door_close_h;
	rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor,
			rays->y_was_adoor);
}

void	draw_ray(cub3d_t *cub, ray_t *rays)
{
	double	distH;
	double	distV;

	distH = dist(cub->x, cub->y, rays->xH, rays->yH);
	distV = dist(cub->x, cub->y, rays->xV, rays->yV);
	rays->is_door_close = 0;
	if (distH < distV)
		draw_ray_v2(cub, rays, distH);
	else
	{
		rays->rx = rays->xV;
		rays->ry = rays->yV;
		rays->dist = distV;
		rays->is_hori = 1;
		rays->is_door = rays->is_door_v;
		rays->x_was_adoor = rays->xv_was_adoor;
		rays->y_was_adoor = rays->yv_was_adoor;
		rays->is_door_close = rays->is_door_close_v;
		rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor,
				rays->y_was_adoor);
	}
}
