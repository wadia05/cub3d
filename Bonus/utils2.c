/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:41:36 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/26 22:15:35 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook_v2(cub3d_t *cub3d, float *x, float *y)
{
	if (mlx_is_key_down(cub3d->win, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->win);
	if (mlx_is_key_down(cub3d->win, MLX_KEY_W))
	{
		(*x) += cos(cub3d->angle) * SPEED;
		(*y) += sin(cub3d->angle) * SPEED;
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_S))
	{
		(*x) -= cos(cub3d->angle) * SPEED;
		(*y) -= sin(cub3d->angle) * SPEED;
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_D))
	{
		(*x) += cos(cub3d->angle + P1) * SPEED;
		(*y) += sin(cub3d->angle + P1) * SPEED;
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_A))
	{
		(*x) -= cos(cub3d->angle + P1) * SPEED;
		(*y) -= sin(cub3d->angle + P1) * SPEED;
	}
}

void	ft_hook_v3(cub3d_t *cub3d)
{
	if (mlx_is_key_down(cub3d->win, MLX_KEY_LEFT))
	{
		cub3d->angle -= ROTATION_SPEED;
		if (cub3d->angle < 0)
			cub3d->angle += 2 * PI;
		cub3d->xdx = cos(cub3d->angle) * SPEED;
		cub3d->ydy = sin(cub3d->angle) * SPEED;
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_RIGHT))
	{
		cub3d->angle += ROTATION_SPEED;
		if (cub3d->angle > 2 * PI)
			cub3d->angle -= 2 * PI;
		cub3d->xdx = cos(cub3d->angle) * SPEED;
		cub3d->ydy = sin(cub3d->angle) * SPEED;
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_C))
		cub3d = open_close_door(cub3d, 1);
}

void	init_player_v2(cub3d_t *cub, int x, int y)
{
	if (cub->map[y][x] == 'W')
		cub->angle = PI;
	else if (cub->map[y][x] == 'N')
		cub->angle = 3 * P1;
	else if (cub->map[y][x] == 'S')
		cub->angle = P1;
	else if (cub->map[y][x] == 'E')
		cub->angle = 0.0;
	cub->x = x * cub->map_unit + cub->map_unit / 2;
	cub->y = y * cub->map_unit + cub->map_unit / 2;
	cub->map[y][x] = '0';
}
void	init_player(cub3d_t *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map_y)
	{
		x = 0;
		while (x < cub->map_x && cub->map[y][x])
		{
			if (cub->map[y][x] != '0' && cub->map[y][x] != '1'
				&& cub->map[y][x] != ' ' && cub->map[y][x] != '\t'
				&& cub->map[y][x] != '3' && cub->map[y][x] != '5')
				init_player_v2(cub, x, y);
			x++;
		}
		y++;
	}
	return ;
}

cub3d_t	*init_cub_v1(map_list_t *stc, map_t *color)
{
	cub3d_t *cub3d;

	cub3d = malloc(sizeof(cub3d_t));
	if (!cub3d)
		return (NULL);
	cub3d->num_rays = 1024;
	cub3d->ray = malloc(sizeof(ray_t) * cub3d->num_rays);
	if (!cub3d->ray)
		return (NULL);
	cub3d->info = color;
	if (stc->width_x > stc->high_y)
	{
		cub3d->map_unit = 64;
		stc->ws = stc->width_x;
	}
	else
	{
		cub3d->map_unit = 64;
		stc->ws = stc->high_y;
	}
	cub3d->map_x = stc->width_x;
	cub3d->map_y = stc->high_y;
	return (cub3d);
}