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
            {
                rays->dof = cub->ray_dof_max;
                rays->is_door_h = 0;
                // printf("mx : %d  my : %d\n", mx, my);
            }
			else if(cub->map[my][mx] == '3')
			{
				rays->dof = cub->ray_dof_max;
				rays->is_door_h = 1;
				//rays->is_door = 1 mean  is a door

			}
			else if(cub->map[my][mx] == '5')
			{
				rays->is_door_close_h = 1;
                rays->xh_was_adoor = rays->xH;
                rays->yh_was_adoor = rays->yH;
                rays->xH += rays->xo;
                rays->yH += rays->yo;
                rays->dof += 1;
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
        rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.0001;
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
            {
                rays->dof = cub->ray_dof_max;
                rays->is_door_v = 0;
            }
			else if(cub->map[my][mx] == '3')
			{   //
				rays->dof = cub->ray_dof_max;
				rays->is_door_v = 1;
				//rays->is_door = 1 mean  is a door

			}
			else if(cub->map[my][mx] == '5')
			{
				rays->is_door_close_v = 1;
                rays->xv_was_adoor = rays->xV;
                rays->yv_was_adoor = rays->yV;
                rays->xV += rays->xo;
                rays->yV += rays->yo;
                rays->dof += 1;
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
        rays->xV = (floor(cub->x / cub->map_unit)) * cub->map_unit - 0.0001 ;
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
        // int mx = (int)(cub->x) / cub->map_unit;
        // int my = (int)(cub->y) / cub->map_unit;
        // printf("mx : %d  my : %d\n", mx, my);

	itirate_vertical(rays, cub);
}

void draw_ray(cub3d_t *cub, ray_t *rays)
{
    double distH;
    double distV;

	distH = dist(cub->x, cub->y, rays->xH, rays->yH);
	distV = dist(cub->x, cub->y, rays->xV, rays->yV);

    rays->is_door_close = 0;
    if (distH < distV)
	{
        rays->rx = rays->xH;
        rays->ry = rays->yH;
        rays->dist = distH;
        rays->is_hori = 0;
        rays->is_door = rays->is_door_h;
        rays->x_was_adoor = rays->xh_was_adoor;
        rays->y_was_adoor = rays->yh_was_adoor;
        rays->is_door_close = rays->is_door_close_h;
        rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor, rays->y_was_adoor);
    }
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
        rays->dist_door = dist(cub->x, cub->y, rays->x_was_adoor, rays->y_was_adoor);
        // if (rays->is_door == 2)
        // {
        //     int mx = (int)(rays->xH) / cub->map_unit;
        //     int my = (int)(rays->yH) / cub->map_unit;
        //     printf("mx : %d  my : %d\n", mx, my);
        // }
    }
}

