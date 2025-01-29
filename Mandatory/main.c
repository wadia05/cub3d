/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:36 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/29 12:57:16 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_hook_mouse(void *param)
// {
// 	t_cub3d	*cub3d;
// 	float	rotation_speed;
// 	float	speed;
// 	float	delta_x;

// 	speed = 2;
// 	rotation_speed = 0.001;
// 	cub3d = param;
// 	if (!cub3d || !cub3d->win)
// 		return ;
// 	mlx_set_cursor_mode(cub3d->win, MLX_MOUSE_HIDDEN);
// 	mlx_get_mouse_pos(cub3d->win, &cub3d->mouse_x, &cub3d->mouse_y);
// 	delta_x = cub3d->mouse_x - WIDTH / 2;
// 	cub3d->angle += delta_x * rotation_speed;
// 	cub3d->angle = fmod(cub3d->angle, 2 * PI);
// 	if (cub3d->angle < 0)
// 		cub3d->angle += 2 * PI;
// 	cub3d->xdx = cos(cub3d->angle) * speed;
// 	cub3d->ydy = sin(cub3d->angle) * speed;
// 	mlx_set_mouse_pos(cub3d->win, WIDTH / 2, HEIGHT / 2);
// }



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
