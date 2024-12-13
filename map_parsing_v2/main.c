/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:56:56 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/13 21:49:52 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3d.h"

int	initialize_and_validate(int ac, char **av, map_t **stc,
		tracker_t **free_head)
{
	if (ac != 2)
		return (print_error("Usage: ./cub3D map.cub"));
	if (validate_file_extension(av[1]))
		return (1);
	*free_head = NULL;
	*stc = init_map_structure(*free_head);
	(*stc)->free_head = *free_head;
	if (!*stc)
		return (print_error("Memory allocation failed"));
	return (0);
}

int	process_map_file(map_t *stc, char *filename, tracker_t **free_head)
{
	int		file;
	char	*line;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		free_all_allocate(free_head);
		return (print_error("Cannot open map file"));
	}
	line = get_next_line(file);
	while (line != NULL)
	{
		if (parse_line(stc, line))
		{
			free(line);
			close_file(file);
			free_all_allocate(free_head);
			return (1);
		}
		free(line);
		line = get_next_line(file);
	}
	close_file(file);
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

// void	print_map_data(map_list_t *current)
// {
// 	while (current != NULL)
// 	{
// 		printf("Map: |%s|\n", current->map);
// 		current = current->next;
// 	}
// }
void fill_maps(map_t *stc)
	{
		map_list_t *current = stc->map_data;
		int y_find = 0;
		int x_find = 0;
		while (current != NULL) {
			// printf("Map: |%s|\n", current->map);
			// printf("len = %d\n", current->length);
			// printf("ws = %d\n", current->ws);
			if (current->length > x_find)
				x_find = current->length;
			y_find++;
			current = current->next;
		}
		stc->map_data->width_x = x_find;
		stc->map_data->high_y = y_find;       

		return ;
	}
	
int	main(int ac, char **av)
{
	map_t		*stc;
	tracker_t	*free_head;
	int			init_result;
	int			file_process_result;
	int			config_validation_result;

	// Initialize and validate input
	init_result = initialize_and_validate(ac, av, &stc, &free_head);
	if (init_result != 0)
		return (init_result);
	// Process map file
	file_process_result = process_map_file(stc, av[1], &free_head);
	if (file_process_result != 0)
		return (file_process_result);
	// Validate map configuration
	config_validation_result = validate_map_config(stc);
	if (config_validation_result != 0)
	{
		free_all_allocate(&free_head);
		return (config_validation_result);
	}
	// Parse map lines
	if (parse_line_maps(stc) != 0)
	{
		free_all_allocate(&free_head);
		return (0);
	}
	fill_maps(stc);
	main2(stc->map_data);
	// Debug: print map data (optional)
	// print_map_data(stc->map_data);
	// Clean up resources
	free_all_allocate(&free_head);
	return (0);
}
