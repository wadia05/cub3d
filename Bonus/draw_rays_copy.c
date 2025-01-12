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

void itirate_horizontal(ray_t *rays, cub3d_t *cub)
{
    rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
        int mx = (int)(rays->xH) / cub->map_unit;
        int my = (int)(rays->yH) / cub->map_unit;
        
        if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
            if (cub->map[my][mx] == '1')
                rays->dof = cub->ray_dof_max;
			else if(cub->map[my][mx] == '3')
			{
				rays->dof = cub->ray_dof_max;
				rays->is_door = 1;
				//rays->is_door = 1 mean  is a door

			}
			else if(cub->map[my][mx] == '5')
			{
				rays->dof = cub->ray_dof_max;
				rays->is_door = 2;
				//rays->is_door = 2 mean was a door

			}
			else
			{
                rays->xH += rays->xo;
                rays->yH += rays->yo;
                rays->dof += 1;
            }
        }
		else
            rays->dof = cub->ray_dof_max;
    }
}

void handle_horizontal_ray(cub3d_t *cub, double start_angle, ray_t *rays)
{
    rays->dof = 0;
    rays->aTan = -1.0 / tan(start_angle);
    if (start_angle > PI)
	{
        rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.005;
        rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
        rays->yo = -cub->map_unit;  
        rays->xo = -rays->yo * rays->aTan;
    }
	else if (start_angle < PI)
	{
        rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit + cub->map_unit;
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

void itirate_vertical(ray_t *rays, cub3d_t *cub)
{
    rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
        int mx = (int)(rays->xV) / cub->map_unit;
        int my = (int)(rays->yV) / cub->map_unit;
        
        if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
            if (cub->map[my][mx] == '1')
                rays->dof = cub->ray_dof_max;
			else if(cub->map[my][mx] == '3')
			{
				rays->dof = cub->ray_dof_max;
				rays->is_door = 1;
				//rays->is_door = 1 mean  is a door

			}
			else if(cub->map[my][mx] == '5')
			{
				rays->dof = cub->ray_dof_max;
				rays->is_door = 2;
				//rays->is_door = 2 mean was a door

			}
			else
			{
                rays->xV += rays->xo;
                rays->yV += rays->yo;
                rays->dof += 1;
            }
        }
		else
            rays->dof = cub->ray_dof_max;
    }
}

void handle_vertical_ray(cub3d_t *cub, double start_angle, ray_t *rays)
{
    rays->dof = 0;
    rays->aTan = -tan(start_angle);
    if (start_angle > PI / 2 && start_angle < 3 * PI / 2)
	{
        rays->xV = (floor(cub->x / cub->map_unit)) * cub->map_unit - 0.005 ;
        rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;
        rays->xo = -cub->map_unit;
        rays->yo = -rays->xo * rays->aTan;
    }
	else if (start_angle < PI / 2 || start_angle > 3 * PI / 2)
	{
        rays->xV = (floor(cub->x / cub->map_unit)) * cub->map_unit + cub->map_unit;
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

void draw_ray(cub3d_t *cub, ray_t *rays)
{
    double distH;
    double distV;

	distH = dist(cub->x, cub->y, rays->xH, rays->yH);
	distV = dist(cub->x, cub->y, rays->xV, rays->yV);
    if (distH < distV)
	{
        rays->rx = rays->xH;
        rays->ry = rays->yH;
        rays->dist = distH;
        rays->is_hori = 0;
    }
	else
	{
        rays->rx = rays->xV;
        rays->ry = rays->yV;
        rays->dist = distV;
        rays->is_hori = 1;
    }
}

