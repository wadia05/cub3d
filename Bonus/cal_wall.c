/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:04 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 21:42:42 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_Bonus.h"

static char	*generate_kick_filename(int index, char *filename)
{
	filename[0] = (index + 1) / 10 + '0';
	filename[1] = (index + 1) % 10 + '0';
	filename[2] = '.';
	filename[3] = 'p';
	filename[4] = 'n';
	filename[5] = 'g';
	filename[6] = '\0';
	return (ft_strjoin("kick/", filename));
}

static int	load_kick_frames(t_map *mp)
{
	char	filename[20];
	char	*path;
	int		i;

	i = 0;
	mp->kickpng = malloc(sizeof(mlx_texture_t *) * 23);
	if (!mp->kickpng)
		return (1);
	while (i < 23)
	{
		path = generate_kick_filename(i, filename);
		mp->kickpng[i] = mlx_load_png(path);
		if (!path || !(mp->kickpng[i]))
		{
			free(path);
			while (--i >= 0)
				mlx_delete_texture(mp->kickpng[i]);
			free(mp->kickpng);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	loading_image(t_map *mp)
{
	mp->no_png = mlx_load_png(mp->no);
	if (!mp->no_png)
		return (1);
	mp->so_png = mlx_load_png(mp->so);
	if (!mp->so_png)
		return (1);
	mp->ea_png = mlx_load_png(mp->ea);
	if (!mp->ea_png)
		return (1);
	mp->we_png = mlx_load_png(mp->we);
	if (!mp->we_png)
		return (1);
	mp->door_png = mlx_load_png("wall_image/door.png");
	if (!mp->door_png)
		return (1);
	if (load_kick_frames(mp))
		return (1);
	return (0);
}

mlx_texture_t	*get_texturte(t_cub3d *cub, t_ray *ray, double s_agl)
{
	if (ray->is_door == 1)
		return (cub->info->door_png);
	else if (!ray->is_hori)
	{
		if (s_agl > 0 && s_agl < PI)
			return (cub->info->so_png);
		else
			return (cub->info->no_png);
	}
	else
	{
		if (s_agl > PI / 2 && s_agl < 3 * PI / 2)
			return (cub->info->we_png);
		else
			return (cub->info->ea_png);
	}
	return (NULL);
}
