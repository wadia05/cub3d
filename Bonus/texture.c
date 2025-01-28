/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:37:16 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/28 20:31:47 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_Bonus.h"

int	calculate_texture_x_coordinate(t_cub3d *cub, t_ray *ray, double s_agl)
{
	t_map	*txtur;
	float	texture_x;
	int		tex_x;

	txtur = cub->info;
	texture_x = 0;
	if (!ray->is_hori)
	{
		texture_x = fmod(ray->rx, cub->map_unit) / cub->map_unit;
		if (s_agl > 0 && s_agl < PI)
			texture_x = 1.0 - texture_x;
	}
	else
	{
		texture_x = fmod(ray->ry, cub->map_unit) / cub->map_unit;
		if (s_agl > PI / 2 && s_agl < 3 * PI / 2)
			texture_x = 1.0 - texture_x;
	}
	tex_x = (int)(texture_x * txtur->wall_texture->width);
	return (tex_x);
}

void	wall_top_bottom(t_cub3d **cub, t_ray *ray, double s_agl)
{
	float	overflow;
	t_map	*txtur;

	txtur = (*cub)->info;
	txtur->fov = PI / 3;
	txtur->dist_project_plane = (WIDTH / 2) / tan(txtur->fov / 2);
	txtur->corrected_distance = ray->dist * cos((*cub)->angle - s_agl);
	txtur->wall_strip_height = ((*cub)->map_unit / txtur->corrected_distance)
		* txtur->dist_project_plane;
	txtur->wall_top = (HEIGHT / 2) - (txtur->wall_strip_height / 2);
	txtur->wall_bottom = (HEIGHT / 2) + (txtur->wall_strip_height / 2);
	txtur->texture_offset = 0.0f;
	if (txtur->wall_strip_height > HEIGHT)
	{
		overflow = txtur->wall_strip_height - HEIGHT;
		txtur->texture_offset = (overflow / 2) / txtur->wall_strip_height;
	}
	txtur->wall_top = fmax(0, txtur->wall_top);
	txtur->wall_bottom = fmin(txtur->wall_bottom, HEIGHT - 1);
	txtur->wall_texture = NULL;
	txtur->wall_texture = get_texturte(*cub, ray, s_agl);
}

uint32_t	get_color_px(t_cub3d *cub, int texY, int texX)
{
	float		shade_factor;
	uint32_t	color;
	t_map		*txtur;

	txtur = cub->info;
	if ((txtur->wall_texture->width * txtur->wall_texture->height * 4) \
		< ((texY * txtur->wall_texture->width + texX) * 4))
	{
		color = 0x00000000;
		return (color);
	}
	cub->r = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width
			+ texX) * 4];
	cub->g = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width
			+ texX) * 4 + 1];
	cub->b = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width
			+ texX) * 4 + 2];
	cub->a = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width
			+ texX) * 4 + 3];
	shade_factor = 1.0f - (txtur->corrected_distance / (cub->map_unit * 10.0f));
	shade_factor = fmaxf(0.1f, fminf(shade_factor, 1.0f));
	color = ((uint8_t)(cub->r * shade_factor) << 24 | (uint8_t)(cub->g
				* shade_factor) << 16 | (uint8_t)(cub->b
				* shade_factor) << 8 | cub->a);
	return (color);
}

void	draw_textured_wall_strip(t_cub3d *cub, int ray_index, int texX)
{
	t_map	*txtur;
	float	screen_pos;
	float	texture_y;
	int		tex_y;
	int		y;

	txtur = cub->info;
	y = txtur->wall_top;
	while (y <= txtur->wall_bottom)
	{
		screen_pos = (float)(y - txtur->wall_top) / (txtur->wall_bottom
				- txtur->wall_top);
		texture_y = txtur->texture_offset + (screen_pos * (1.0f - 2.0f
					* txtur->texture_offset));
		tex_y = (int)(texture_y * txtur->wall_texture->height);
		tex_y = fmax(0, fmin(tex_y, txtur->wall_texture->height - 1));
		mlx_put_pixel(cub->img, ray_index, y, get_color_px(cub, tex_y, texX));
		y++;
	}
}

void	draw_wall(t_cub3d *cub, t_ray *ray, int ray_index, double s_agl)
{
	int	tex_x;

	wall_top_bottom(&cub, ray, s_agl);
	tex_x = calculate_texture_x_coordinate(cub, ray, s_agl);
	render_ceiling(cub, ray_index);
	draw_textured_wall_strip(cub, ray_index, tex_x);
	render_floor(cub, ray_index);
}
