/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:45:18 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/27 15:54:41 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(cub3d_t *cub)
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
	float prev_positions_x[5];
	float prev_positions_y[5];

	// Calculate previous positions based on current position and direction
	for (int i = 0; i < 5; i++)
	{
		// Calculate positions going backwards from current position
		prev_positions_x[i] = cub->x + (cos(cub->angle) * (i * 2));
		prev_positions_y[i] = cub->y + (sin(cub->angle) * (i * 2));
	}
		for (int i = 0; i < 5; i++)
	{
        // Calculate screen position for tail segment
        int screen_x = 50 + (int)((prev_positions_x[i] - cub->x) * CELL_SIZE / CELL_SIZE);
        int screen_y = 50 + (int)((prev_positions_y[i] - cub->y) * CELL_SIZE / CELL_SIZE);
        
        // Calculate fade effect (alpha) based on position in tail
        int alpha = 255 - ((i * 255) / 5);
        // Create yellow color with fade effect
        int tail_color = 0x00FFFF00 | (alpha << 24);
        
        // Draw tail segment if it's within map boundaries
        if (screen_x >= 0 && screen_x < MAP_SIZE && screen_y >= 0 && screen_y < MAP_SIZE)
            mlx_put_pixel(cub->img, screen_x, screen_y, tail_color);
    }
}

void	draw_cell(cub3d_t *cub, int x, int y, int map_x, int map_y)
{
	char	map_char;

	if (map_y >= 0 && map_y < HEIGHT && map_x >= 0 && map_x < WIDTH)
	{
		map_char = cub->map[map_y][map_x];
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

void	draw_mini_map(cub3d_t *cub)
{
	int	y;
	int	map_y;
	int	map_x;
	int	x;

	y = 0;
	while (y < MAP_SIZE)
	{
		x = 0;
		while (x < MAP_SIZE)
		{
			map_x = (cub->x + x - 50) / CELL_SIZE;
			map_y = (cub->y + y - 50) / CELL_SIZE;
			draw_cell(cub, x, y, map_x, map_y);
			x++;
		}
		y++;
	}
	draw_player(cub);
}

cub3d_t	*open_close_door(cub3d_t *cub, int k)
{
	int i;
	int j;

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