/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:58:23 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/29 18:45:48 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (cub->map[my][mx] == '1')
				rays->dof = cub->ray_dof_max;
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
			if (cub->map[my][mx] == '1')
				rays->dof = cub->ray_dof_max;
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
