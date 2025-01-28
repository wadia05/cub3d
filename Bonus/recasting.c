/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:58:23 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/28 20:32:34 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_Bonus.h"

void	itirate_horizontal_v2(t_ray *rays, t_cub3d *cub, int mx, int my)
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
		rays->xh_was_adoor = rays->xh;
		rays->yh_was_adoor = rays->yh;
		rays->xh += rays->xo;
		rays->yh += rays->yo;
		rays->dof += 1;
	}
}

void	itirate_horizontal(t_ray *rays, t_cub3d *cub)
{
	int	mx;
	int	my;

	rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
		mx = (int)(rays->xh) / cub->map_unit;
		my = (int)(rays->yh) / cub->map_unit;
		if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
			if (cub->map[my][mx] == '1' || cub->map[my][mx] == '3'
				|| cub->map[my][mx] == '5')
				itirate_horizontal_v2(rays, cub, mx, my);
			else
			{
				rays->xh += rays->xo;
				rays->yh += rays->yo;
				rays->dof += 1;
			}
		}
		else
			rays->dof = cub->ray_dof_max;
	}
}

void	itirate_vertical_v2(t_ray *rays, t_cub3d *cub, int mx, int my)
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
		rays->xv_was_adoor = rays->xv;
		rays->yv_was_adoor = rays->yv;
		rays->xv += rays->xo;
		rays->yv += rays->yo;
		rays->dof += 1;
	}
}

void	itirate_vertical(t_ray *rays, t_cub3d *cub)
{
	int	mx;
	int	my;

	rays->dof = 0;
	while (rays->dof < cub->ray_dof_max)
	{
		mx = (int)(rays->xv) / cub->map_unit;
		my = (int)(rays->yv) / cub->map_unit;
		if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
		{
			if (cub->map[my][mx] == '1' || cub->map[my][mx] == '3'
				|| cub->map[my][mx] == '5')
				itirate_vertical_v2(rays, cub, mx, my);
			else
			{
				rays->xv += rays->xo;
				rays->yv += rays->yo;
				rays->dof += 1;
			}
		}
		else
			rays->dof = cub->ray_dof_max;
	}
}
