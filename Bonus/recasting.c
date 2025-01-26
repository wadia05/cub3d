/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:58:23 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/26 21:58:50 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	itirate_horizontal_v2(ray_t *rays, cub3d_t *cub, int mx, int my)
{
	if (cub->map[my][mx] == '1')
	{
		rays->dof = cub->ray_dof_max;
		rays->is_door_h = 0;
	}
	else if (cub->map[my][mx] == '3')
	{
		rays->dof = cub->ray_dof_max;
		rays->is_door_h = 1;
	}
	else if (cub->map[my][mx] == '5')
	{
		rays->is_door_close_h = 1;
		rays->xh_was_adoor = rays->xH;
		rays->yh_was_adoor = rays->yH;
		rays->xH += rays->xo;
		rays->yH += rays->yo;
		rays->dof += 1;
	}
}

void	itirate_horizontal(ray_t *rays, cub3d_t *cub)
{
	int	mx;
	int	my;

	rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
		mx = (int)(rays->xH) / cub->map_unit;
		my = (int)(rays->yH) / cub->map_unit;
		if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
			if (cub->map[my][mx] == '1' || cub->map[my][mx] == '3'
				|| cub->map[my][mx] == '5')
				itirate_horizontal_v2(rays, cub, mx, my);
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

void	itirate_vertical_v2(ray_t *rays, cub3d_t *cub, int mx, int my)
{
	if (cub->map[my][mx] == '1')
	{
		rays->dof = cub->ray_dof_max;
		rays->is_door_v = 0;
	}
	else if (cub->map[my][mx] == '3')
	{
		rays->dof = cub->ray_dof_max;
		rays->is_door_v = 1;
	}
	else if (cub->map[my][mx] == '5')
	{
		rays->is_door_close_v = 1;
		rays->xv_was_adoor = rays->xV;
		rays->yv_was_adoor = rays->yV;
		rays->xV += rays->xo;
		rays->yV += rays->yo;
		rays->dof += 1;
	}
}
void	itirate_vertical(ray_t *rays, cub3d_t *cub)
{
	int mx;
	int my;

	rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
		mx = (int)(rays->xV) / cub->map_unit;
		my = (int)(rays->yV) / cub->map_unit;
		if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
			if (cub->map[my][mx] == '1' || cub->map[my][mx] == '3'
				|| cub->map[my][mx] == '5')
				itirate_vertical_v2(rays, cub, mx, my);
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