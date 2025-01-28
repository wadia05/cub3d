/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:45:18 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/28 17:55:27 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tail(t_cub3d *cub)
{
	float	prev_positions_x[5];
	float	prev_positions_y[5];
	int		screen_x;
	int		screen_y;
	int		i;

	i = 0;
	while (i < 5)
	{
		prev_positions_x[i] = cub->x + (cos(cub->angle) * (i * 2));
		prev_positions_y[i] = cub->y + (sin(cub->angle) * (i * 2));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		screen_x = 50 + (int)((prev_positions_x[i] - cub->x) * CELL_SIZE
				/ CELL_SIZE);
		screen_y = 50 + (int)((prev_positions_y[i] - cub->y) * CELL_SIZE
				/ CELL_SIZE);
		if (screen_x >= 0 && screen_x < MAP_SIZE && screen_y >= 0
			&& screen_y < MAP_SIZE)
			mlx_put_pixel(cub->img, screen_x, screen_y, PLAYER_COLOR);
		i++;
	}
}

void	draw_player(t_cub3d *cub)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_put_pixel(cub->img, 50 + i, 50 + j, PLAYER_COLOR);
			j++;
		}
		i++;
	}
	draw_tail(cub);
}

void	draw_cell(t_cub3d *cub, int x, int y)
{
	char	map_char;

	if (cub->add_y >= 0 && cub->add_y < HEIGHT && cub->add_x >= 0
		&& cub->add_x < WIDTH)
	{
		map_char = cub->map[cub->add_y][cub->add_x];
		if (map_char == '1')
			mlx_put_pixel(cub->img, x, y, WALL_COLOR);
		else if (map_char == '3')
			mlx_put_pixel(cub->img, x, y, SPECIAL_COLOR);
		else if (map_char == '5')
			mlx_put_pixel(cub->img, x, y, 0x0077CCFF);
		else if (map_char == '0')
			mlx_put_pixel(cub->img, x, y, FLOOR_COLOR);
		else
			mlx_put_pixel(cub->img, x, y, OUT_OF_BOUNDS_COLOR);
	}
	else
		mlx_put_pixel(cub->img, x, y, OUT_OF_BOUNDS_COLOR);
}

void	draw_mini_map(t_cub3d *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_SIZE)
	{
		x = 0;
		while (x < MAP_SIZE)
		{
			cub->add_x = (cub->x + x - 50) / CELL_SIZE;
			cub->add_y = (cub->y + y - 50) / CELL_SIZE;
			draw_cell(cub, x, y);
			x++;
		}
		y++;
	}
	draw_player(cub);
}

t_cub3d	*open_close_door(t_cub3d *cub, int k)
{
	int	i;
	int	j;

	if (k == 0)
	{
		i = floor(cub->ray[500].rx / 64);
		j = floor(cub->ray[500].ry / 64);
		if (cub->ray[500].is_door == 1)
		{
			cub->map[j][i] = '5';
			cub->ray[500].is_door = 2;
		}
	}
	else if (k == 1)
	{
		i = floor(cub->ray[500].x_was_adoor / 64);
		j = floor(cub->ray[500].y_was_adoor / 64);
		if (cub->ray[500].is_door_close == 1)
		{
			cub->map[j][i] = '3';
			cub->ray[500].is_door_close = 0;
		}
	}
	return (cub);
}
