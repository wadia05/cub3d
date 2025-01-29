/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:36 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/29 21:26:55 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_all(t_cub3d *cub3d)
{
	if (cub3d->info)
	{
		if (cub3d->info->no_png)
			mlx_delete_texture(cub3d->info->no_png);
		if (cub3d->info->so_png)
			mlx_delete_texture(cub3d->info->so_png);
		if (cub3d->info->ea_png)
			mlx_delete_texture(cub3d->info->ea_png);
		if (cub3d->info->we_png)
			mlx_delete_texture(cub3d->info->we_png);
		if (cub3d->info->door_png)
			mlx_delete_texture(cub3d->info->door_png);
	}
	if (cub3d->img)
		mlx_delete_image(cub3d->win, cub3d->img);
}
