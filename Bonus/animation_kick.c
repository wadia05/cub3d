/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_kick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:05:52 by abenchel          #+#    #+#             */
/*   Updated: 2025/01/27 16:05:53 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_animation_frames(cub3d_t *cub3d, int i)
{
	while (--i >= 0)
		mlx_delete_image(cub3d->win, cub3d->animation_frames[i]);
	free(cub3d->animation_frames);
}

static int	load_single_frame(cub3d_t *cub3d, int i)
{
	cub3d->animation_frames[i] = mlx_texture_to_image(cub3d->win,
			cub3d->info->Kickpng[i]);
	if (!cub3d->animation_frames[i])
		return (1);
	mlx_resize_image(cub3d->animation_frames[i], WIDTH, HEIGHT);
	if (mlx_image_to_window(cub3d->win, cub3d->animation_frames[i], 0, 0) < 0)
		return (1);
	cub3d->animation_frames[i]->enabled = false;
	return (0);
}

void	init_kick_animation(cub3d_t *cub3d)
{
	int	i;

	cub3d->info->i = 0;
	cub3d->info->last_time = mlx_get_time();
	cub3d->animation_frames = malloc(sizeof(mlx_image_t *) * 23);
	if (!cub3d->animation_frames)
		return ;
	i = -1;
	while (++i < 23)
	{
		if (load_single_frame(cub3d, i))
		{
			cleanup_animation_frames(cub3d, i);
			return ;
		}
	}
}

static void	handle_frame_transition(cub3d_t *cub3d)
{
	if (cub3d->info->i > 0)
		cub3d->animation_frames[cub3d->info->i - 1]->enabled = false;
	cub3d->animation_frames[cub3d->info->i]->enabled = true;
	if (cub3d->info->i == 12)
		cub3d = open_close_door(cub3d, 0);
}

int	update_kick_animation(cub3d_t *cub3d)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - cub3d->info->last_time >= 0.027)
	{
		handle_frame_transition(cub3d);
		cub3d->info->last_time = current_time;
		cub3d->info->i++;
		if (cub3d->info->i >= 23)
		{
			cub3d->animation_frames[22]->enabled = false;
			cub3d->info->i = 0;
			return (0);
		}
	}
	return (1);
}
