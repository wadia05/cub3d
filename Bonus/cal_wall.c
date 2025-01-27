/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:04 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/27 16:52:22 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	load_kick_frames(map_t *mp)
{
	char	filename[20];
	char	*path;
	int		i;

	i = 0;
	mp->Kickpng = malloc(sizeof(mlx_texture_t *) * 23);
	if (!mp->Kickpng)
		return (1);
	while (i < 23)
	{
		path = generate_kick_filename(i, filename);
		mp->Kickpng[i] = mlx_load_png(path);
		if (!path || !(mp->Kickpng[i]))
		{
			free(path);
			while (--i >= 0)
				mlx_delete_texture(mp->Kickpng[i]);
			free(mp->Kickpng);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	loading_image(map_t *mp)
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
	mp->door_png = mlx_load_png("door.png");
	if (!mp->door_png)
		return (1);
	if (load_kick_frames(mp))
		return (1);
	return (0);
}

mlx_texture_t	*get_texturte(cub3d_t *cub, ray_t *ray, double s_agl)
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
