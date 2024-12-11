#include "../mandatory/cub3d.h"

// Function 1: Validate initial arguments and file
int	validate_input_args(int ac, char **av)
{
	if (ac != 2)
	{
		print_error("Usage: ./cub3D map.cub");
		return (1);
	}
	if (validate_file_extension(av[1]))
	{
		return (1);
	}
	return (0);
}

// Function 2: Initialize map structure and allocate resources
map_t	*setup_map_structure(tracker_t **free_head)
{
	map_t	*stc;

	*free_head = NULL;
	stc = init_map_structure(*free_head);
	if (!stc)
	{
		print_error("Memory allocation failed");
		return (NULL);
	}
	stc->free_head = *free_head;
	return (stc);
}

// Function 3: Open map file and handle errors
int	open_map_file(const char *filename, tracker_t **free_head)
{
	int	file;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		free_all_allocate(free_head);
		print_error("Cannot open map file");
		return (-1);
	}
	return (file);
}

// Function 4: Parse map file contents
int	parse_map_file_contents(map_t *stc, int file, tracker_t **free_head)
{
	char	*line;

	while ((line = get_next_line(file)) != NULL)
	{
		if (parse_line(stc, line))
		{
			free(line);
			close_file(file);
			free_all_allocate(free_head);
			return (1);
		}
		free(line);
	}
	// Validate colors and textures
	if (stc->c_color->lock != true || stc->f_color->lock != true)
	{
		print_error("color missing yaaa <");
		return (1);
	}
	if (stc->no == NULL || stc->we == NULL || stc->so == NULL
		|| stc->ea == NULL)
	{
		print_error("texture missing yaaa <");
		return (1);
	}
	return (0);
}

// Function 5: Main function using the above helper functions
int	main(int ac, char **av)
{
	map_t *stc;
	int file;
	tracker_t *free_head;
	map_list_t *current;

	if (validate_input_args(ac, av))
		return (1);
	stc = setup_map_structure(&free_head);
	if (!stc)
		return (1);
	file = open_map_file(av[1], &free_head);
	if (file == -1)
		return (1);
	if (parse_map_file_contents(stc, file, &free_head))
		return (1);

	if (parse_line_maps(stc) != 0)
	{
		close_file(file);
		free_all_allocate(&free_head);
		return (1);
	}

	// current = stc->map_data;
	// while (current != NULL)
	// {
	// 	printf("Map: |%s|\n", current->map);
	// 	current = current->next;
	// }
	close_file(file);
	free_all_allocate(&free_head);

	return (0);
}
