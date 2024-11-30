/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:15:21 by abenchel          #+#    #+#             */
/*   Updated: 2024/11/28 16:15:23 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_moraba3(int x, int y, int color, cub3d_t *cub)
{
    int i = 0;
    int j;
    
    // Reduce the size of each cube by 1 pixel to create a gap
    int cube_size = cub->map_unit;
    
    while (i < cube_size)
    {
        j = 0;
        while(j < cube_size)
        {
            mlx_put_pixel(cub->img, x+i, y+j, color);
            j++;
        }
        i++;
    }
    return 0;
}

void handle_horizontal_ray(cub3d_t *cub, double start_angle, ray_t *rays)
{
    rays->dof = 0;
    rays->aTan = -1.0 / tan(start_angle);
	printf("%f\n",rays->aTan);
    // Handle horizontal lines
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
        rays->dof = 8;
    }

    // Check horizontal intersections
    while (rays->dof < 8) 
	{
        int mx = (int)(rays->xH) / cub->map_unit;
        int my = (int)(rays->yH) / cub->map_unit;
        
        if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y) 
		{

            if (cub->map[my][mx] == 1)
                rays->dof = 8;
			else 
			{
                rays->xH += rays->xo;
                rays->yH += rays->yo;
                rays->dof += 1;
            }
        }
		else
            rays->dof = 8;
    }
}

// Helper function to handle vertical raycasting
void handle_vertical_ray(cub3d_t *cub, double start_angle, ray_t *rays)
{
    rays->dof = 0;
    rays->aTan = -tan(start_angle);  // Changed for clarity

    if (start_angle > PI / 2 && start_angle < 3 * PI / 2)
	{
        rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit - 0.0001;
        rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;
        rays->xo = -cub->map_unit;
        rays->yo = -rays->xo * rays->aTan;
    }
	else if (start_angle < PI / 2 || start_angle > 3 * PI / 2)
	{
        rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit + cub->map_unit;
        rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;
        rays->xo = cub->map_unit;
        rays->yo = -rays->xo * rays->aTan;
    }
	else
	{
        rays->xV = cub->x;
        rays->yV = cub->y;
        rays->dof = 8;
    }
    while (rays->dof < 8)
	{
        int mx = (int)(rays->xV) / cub->map_unit;
        int my = (int)(rays->yV) / cub->map_unit;
        
        if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
            if (cub->map[my][mx] == 1)
                rays->dof = 8;
			else
			{
                rays->xV += rays->xo;
                rays->yV += rays->yo;
                rays->dof += 1;
            }
        }
		else
            rays->dof = 8;
    }
}

// Helper function to draw a ray
void draw_ray(cub3d_t *cub, ray_t *rays)
{
    double distH = dist(cub->x, cub->y, rays->xH, rays->yH);
    double distV = dist(cub->x, cub->y, rays->xV, rays->yV);

    if (distH < distV)
	{
        rays->rx = rays->xH;
        rays->ry = rays->yH;
        rays->dist = distH;
        draw_line(cub->img, (int)cub->x , (int)cub->y , (int)rays->rx, (int)rays->ry, 0xFFFF00FF);
    }
	else
	{
        rays->rx = rays->xV;
        rays->ry = rays->yV;
        rays->dist = distV;
        draw_line(cub->img, (int)cub->x , (int)cub->y , (int)rays->rx, (int)rays->ry, 0xFF4500FF);
    }
}

// Function to draw all rays
int draw_rays(cub3d_t *cub) 
{
    if (init_ray(cub)) return 1;  // Initialize ray (malloc failure check)

    ray_t *rays = cub->ray;
    rays->distH = 10000000;
    rays->distV = 10000000;
    rays->xH = cub->x;
    rays->yH = cub->y;
    rays->xV = cub->x;
    rays->yV = cub->y;

    float start_angle = cub->angle - (30 * DR);
    if (start_angle < 0) start_angle += 2 * PI;
    if (start_angle > 2 * PI) start_angle -= 2 * PI;

    for (int i = 0; i < cub->num_rays; i++)
	{
        handle_horizontal_ray(cub, start_angle, rays);
        handle_vertical_ray(cub, start_angle, rays);
        draw_ray(cub, rays);

        start_angle += DR;
        if (start_angle < 0) start_angle += 2 * PI;
        if (start_angle > 2 * PI) start_angle -= 2 * PI;
    }

    return 0;
}