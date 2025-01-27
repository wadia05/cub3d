#include "cub3d.h"

void	handle_animation(cub3d_t *cub3d)
{
	static bool	animation_loaded = false;
	static bool	animation_in_progress = false;

	if (mlx_is_key_down(cub3d->win, MLX_KEY_O))
	{
		if (!animation_loaded && (animation_loaded = true))
			init_kick_animation(cub3d);
		if (!animation_in_progress)
			animation_in_progress = true;
	}
	if (animation_in_progress)
		animation_in_progress = update_kick_animation(cub3d);
}

void	handle_movement(cub3d_t *cub3d)
{
	float	x = cub3d->x;
	float	y = cub3d->y;
	int		check;

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
	cub3d_t	*cub3d = param;

	handle_animation(cub3d);
	handle_movement(cub3d);
	draw_rays(cub3d);
	draw_mini_map(cub3d);
}

void	ft_hook_mouse(void *param)
{
	cub3d_t			*cub3d;
	static int32_t	prev_x = WIDTH / 2;
	const float		rotation_speed = 0.001;
	const float		speed = 2;
	float			delta_x;

	cub3d = param;
	int32_t mouse_x, mouse_y;
	if (!cub3d || !cub3d->win)
		return ;
	// Hide cursor at game start
	mlx_set_cursor_mode(cub3d->win, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(cub3d->win, &mouse_x, &mouse_y);
	delta_x = mouse_x - prev_x;
	cub3d->angle += delta_x * rotation_speed;
	cub3d->angle = fmod(cub3d->angle, 2 * PI);
	if (cub3d->angle < 0)
		cub3d->angle += 2 * PI;
	cub3d->xdx = cos(cub3d->angle) * speed;
	cub3d->ydy = sin(cub3d->angle) * speed;
	mlx_set_mouse_pos(cub3d->win, WIDTH / 2, HEIGHT / 2);
}

void	cleanup_all(cub3d_t *cub3d)
{
	int	i;

	if (cub3d->animation_frames)
	{
		i = 0;
		while (i < 23)
		{
			if (cub3d->animation_frames[i])
				mlx_delete_image(cub3d->win, cub3d->animation_frames[i]);
			i++;
		}
		free(cub3d->animation_frames);
	}
	if (cub3d->info && cub3d->info->Kickpng)
	{
		i = 0;
		while (i < 23)
		{
			if (cub3d->info->Kickpng[i])
				mlx_delete_texture(cub3d->info->Kickpng[i]);
			i++;
		}
		free(cub3d->info->Kickpng);
	}
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
	// Cleanup main image if it exists
	if (cub3d->img)
		mlx_delete_image(cub3d->win, cub3d->img);
	// Cleanup MLX window
	// if (cub3d->win)
	// 	mlx_terminate(cub3d->win);
}

cub3d_t	*remake_map(map_list_t *stc, cub3d_t *cub3d)
{
	map_list_t	*current;
	int			i;
	int			j;

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
	return (cub3d);
}

cub3d_t	*main2_v2(cub3d_t *cub3d, map_list_t *stc, map_t *color)
{
	cub3d->fov = 60;
	cub3d = remake_map(stc, cub3d);
	loading_image(color);
	init_player(cub3d);
	cub3d->pa = 0.0;
	cub3d->xdx = cos(cub3d->angle) * 5;
	cub3d->ydy = sin(cub3d->angle) * 5;
	cub3d->ray_dof_max = stc->ws;
	// free(stc);
	cub3d->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!cub3d->win)
	{
		free_all_allocate(color->free_head);
		free_all(cub3d);
		return (NULL);
	}
	return (cub3d);
}
void	main2(map_list_t *stc, map_t *color)
{
	cub3d_t	*cub3d;

	cub3d = init_cub_v1(stc, color);
	cub3d = main2_v2(cub3d, stc, color);
	cub3d->img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
	if (!cub3d->img)
	{
		free_all_allocate(color->free_head);
		mlx_terminate(cub3d->win);
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
	mlx_loop_hook(cub3d->win, ft_hook_mouse, cub3d);
	mlx_loop(cub3d->win);
	cleanup_all(cub3d);
	free_all(cub3d);
	return ;
}
