/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:49:44 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 19:08:51 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	handle_animation(t_cub3d *cub3d)
// {
// 	static bool	animation_loaded = false;
// 	static bool	animation_in_progress = false;

// 	if (mlx_is_key_down(cub3d->win, MLX_KEY_O))
// 	{
// 		if (!animation_loaded)
// 		{
// 			animation_loaded = true;
// 			init_kick_animation(cub3d);
// 		}
// 		if (!animation_in_progress)
// 			animation_in_progress = true;
// 	}
// 	if (animation_in_progress)
// 		animation_in_progress = update_kick_animation(cub3d);
// }

void	handle_movement(t_cub3d *cub3d)
{
	float	x;
	float	y;
	int		check;

	x = cub3d->x;
	y = cub3d->y;
	ft_hook_v2(cub3d, &x, &y);
	ft_hook_v3(cub3d);
	check = check_mov(x, y, cub3d);
	if (check == 0)
	{
		cub3d->x = x;
		cub3d->y = y;
	}
}

void	ft_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	// handle_animation(cub3d);
	handle_movement(cub3d);
	draw_rays(cub3d);
}
