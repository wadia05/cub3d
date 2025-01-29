/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:49:41 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 12:57:26 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remake_v2(t_map_list *current, t_cub3d *cub3d)
{
	int	i;
	int	j;

	j = 0;
	while (current)
	{
		i = 0;
		while (i < cub3d->map_x && current->map[i])
		{
			cub3d->map[j][i] = current->map[i];
			i++;
		}
		j++;
		current = current->next;
	}
}

t_cub3d	*remake_map(t_map_list *stc, t_cub3d *cub3d)
{
	t_map_list	*current;
	int			i;

	current = stc;
	i = 0;
	cub3d->map = malloc(sizeof(char *) * cub3d->map_y);
	if (!cub3d->map)
		return (NULL);
	while (i < cub3d->map_y)
	{
		cub3d->map[i] = malloc(sizeof(char) * (cub3d->map_x + 1));
		if (!cub3d->map[i])
			return (NULL);
		ft_memset((void *)cub3d->map[i], 0, cub3d->map_x + 1);
		i++;
	}
	remake_v2(current, cub3d);
	return (cub3d);
}

t_cub3d	*main2_v2(t_cub3d *cub3d, t_map_list *stc, t_map *color)
{
	cub3d->fov = 60;
	cub3d = remake_map(stc, cub3d);
	loading_image(color);
	init_player(cub3d);
	cub3d->pa = 0.0;
	cub3d->xdx = cos(cub3d->angle) * 5;
	cub3d->ydy = sin(cub3d->angle) * 5;
	cub3d->ray_dof_max = stc->ws;
	cub3d->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!cub3d->win)
	{
		free_all_allocate(color->free_head);
		free_all(cub3d);
		return (NULL);
	}
	return (cub3d);
}

void	main2(t_map_list *stc, t_map *color)
{
	t_cub3d	*cub3d;

	cub3d = init_cub_v1(stc, color);
	cub3d = main2_v2(cub3d, stc, color);
	cub3d->img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
	if (!cub3d->img)
	{
		free_all_allocate(color->free_head);
		free_all(cub3d);
		return ;
	}
	if (mlx_image_to_window(cub3d->win, cub3d->img, 0, 0) < 0)
	{
		free_all_allocate(color->free_head);
		mlx_delete_image(cub3d->win, cub3d->img);
		mlx_terminate(cub3d->win);
		free_all(cub3d);
		return ;
	}
	mlx_loop_hook(cub3d->win, ft_hook, cub3d);
	// mlx_loop_hook(cub3d->win, ft_hook_mouse, cub3d);
	mlx_loop(cub3d->win);
	cleanup_all(cub3d);
	free_all(cub3d);
}
