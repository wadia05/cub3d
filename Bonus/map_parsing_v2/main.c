/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:24 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/27 18:55:34 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	initialize_and_validate(int ac, char **av, map_t **stc,
		tracker_t **free_head)
{
	if (ac != 2)
		return (print_error("Usage: ./cub3D map.cub"));
	if (validate_file_extension(av[1]))
		return (1);
	*free_head = NULL;
	*stc = init_map_structure(free_head);
	if (!*stc)
	{
		return (print_error("Memory allocation failed"));
	}
	(*stc)->free_head = free_head;
	return (0);
}

int	validate_map_config(map_t *stc)
{
	if (stc->c_color->lock != true || stc->f_color->lock != true)
		return (print_error("Color missing"));
	if (stc->no == NULL || stc->we == NULL || stc->so == NULL
		|| stc->ea == NULL)
		return (print_error("Texture missing"));
	return (0);
}

void	fill_maps(map_t *stc)
{
	map_list_t	*current;
	int			y_find;
	int			x_find;

	current = stc->map_data;
	y_find = 0;
	x_find = 0;
	while (current != NULL)
	{
		if (current->length > x_find)
			x_find = current->length;
		y_find++;
		current = current->next;
	}
	stc->map_data->width_x = x_find;
	stc->map_data->high_y = y_find;
	return ;
}

static int	process_and_validate(map_t *stc, char *map_file,
		tracker_t **free_head)
{
	int	result;

	result = process_map_file(stc, map_file, free_head);
	if (result != 0)
		return (result);
	result = validate_map_config(stc);
	if (result != 0)
	{
		free_all_allocate(free_head);
		return (result);
	}
	if (parse_line_maps(stc) != 0)
	{
		free_all_allocate(free_head);
		return (0);
	}
	return (0);
}
void leaks (){
	system("leaks cub3d_Bonus");
}

int	main(int ac, char **av)
{
	map_t		*stc;
	tracker_t	*free_head;
	int			result;
	atexit(leaks);
	free_head = NULL;
	result = initialize_and_validate(ac, av, &stc, &free_head);
	if (result != 0)
		return (result);
	result = process_and_validate(stc, av[1], &free_head);
	if (result != 0)
		return (result);
	fill_maps(stc);
	main2(stc->map_data, stc);
	free_all_allocate(&free_head);

	printf("----------------------------------------------------");
	return (0);
}
