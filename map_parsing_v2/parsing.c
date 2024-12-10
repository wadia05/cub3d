    #include "../mandatory/cub3d.h"

    bool is_char_here(const char *line, const char *chars) {
        while (*line) {
            if (ft_strchr(chars, *line)) {
                return true;
            }
            line++;
        }
        return false;
    }

    void trim_end(char *str) {
        int len = ft_strlen(str);
        while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
            str[len - 1] = '\0';
            len--;
        }
    }

    void remove_newline(char *line) {
        char *newline = ft_strchr(line, '\n');
        if (newline) *newline = '\0';
    }

    int print_error( char *str) {
        write(2, "Error\n", 6);
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
        return 1;
    }

    int handle_texture(char **dest, char *path, char *type, char **token) {
        if (*dest != NULL)
            return print_error("Duplicate texture definition");
        if (word_count(token) > 2)
        {
            print_error("more then one path in ");
            return print_error(type);
        }
        if (validate_texture_path(path, type) != 0)
            return 1;
        *dest = ft_strdup(path);
        if (!*dest)
            return print_error("Memory allocation failed");
        return 0;
    }

    map_t *init_map_structure(void) {
        map_t *stc = tracker_malloc(sizeof(map_t));
        if (!stc) return NULL;
        ft_memset(stc, 0, sizeof(map_t));

        if (!(stc->f_color = tracker_malloc(sizeof(color_t))) || 
            !(stc->c_color = tracker_malloc(sizeof(color_t)))) {
            free_all_allocate();
            return NULL;
        }
        ft_memset(stc->f_color, 0, sizeof(color_t));
        ft_memset(stc->c_color, 0, sizeof(color_t));

        return stc;
    }

int parse_texture_line(map_t *stc, char **tokens) {
    if (!tokens[1]) {  // Add this check
        return print_error("Missing texture path");
    }
    
    if (ft_strncmp(tokens[0], "NO", 3) == 0)
        return handle_texture(&stc->no, tokens[1], "NO", tokens);
    else if (ft_strncmp(tokens[0], "SO", 3) == 0)
        return handle_texture(&stc->so, tokens[1], "SO", tokens);
    else if (ft_strncmp(tokens[0], "WE", 3) == 0)
        return handle_texture(&stc->we, tokens[1], "WE", tokens);
    else if (ft_strncmp(tokens[0], "EA", 3) == 0)
        return handle_texture(&stc->ea, tokens[1], "EA", tokens);
    return print_error("Unknown texture identifier");
}

    int parse_color_line(map_t *stc, char **tokens, char *line) {
        if (ft_strncmp(tokens[0], "F", 2) == 0 && line) {
            if (parse_color(line, stc->f_color) != 0)
                return print_error("Invalid floor color format");
        } else if (ft_strncmp(tokens[0], "C", 2) == 0 && line) {
            if (parse_color(line, stc->c_color) != 0)
                return print_error("Invalid ceiling color format");
        } else {
            return print_error("Invalid color identifier");
        }
        return 0;
    }


int parse_line(map_t *stc, char *line) {
    int ret = 0;
    if (!stc || !line) {
        return print_error("NULL pointer in parse_line");
    }

    remove_newline(line);
    trim_end(line);

    if ( line[0] == '\0' && line[1] == '\0' && stc->map_str == true)
    {
        stc->map_data = add_map_list(stc->map_data, "\n");
    }

    char **tokens = ft_split(line, ' ');
    if (!tokens) 
        return print_error("Memory allocation failed");

    if (tokens[0]) {
        if (ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "SO", 2) == 0 ||
            ft_strncmp(tokens[0], "WE", 2) == 0 || ft_strncmp(tokens[0], "EA", 2) == 0) {
            if (stc->map_str == true) {
                ret = print_error("Map is not at the end");
            } else {
                ret = parse_texture_line(stc, tokens);
            }
        } else if (ft_strncmp(tokens[0], "F", 1) == 0 || ft_strncmp(tokens[0], "C", 1) == 0) {
            ret = parse_color_line(stc, tokens, line);
        } else if (is_char_here(line, "01WSEN")) {
            stc->map_str = true;
            if (!is_char_here(line, "01WSEN \t")) {
                ret = print_error("Invalid character in map");
            } else {
                stc->map_data = add_map_list(stc->map_data, line);
            }
        } else {
            ret = print_error("Invalid identifier");
        }
    }

    free_split(tokens);
    return ret;
}

    void close_file(int file) {
        char *line;
        while ((line = get_next_line(file)) != NULL) {
            free(line);
        }
        close(file);
    }




void fill_maps(map_t *stc)
	{
		map_list_t *current = stc->map_data;
		int y_find = 0;
		int x_find = 0;
		while (current != NULL) {
			printf("Map: |%s|\n", current->map);
			printf("len = %d\n", current->length);
			printf("ws = %d\n", current->ws);
			if (current->length > x_find)
				x_find = current->length;
			y_find++;
			current = current->next;
		}
		stc->map_data->width_x = x_find;
		stc->map_data->high_y = y_find;       

		return ;
	}

int main(int ac, char **av) {
    if (ac != 2) return print_error("Usage: ./cub3D map.cub");

    if (validate_file_extension(av[1])) return 1;
    
    map_t *stc = init_map_structure();
    if (!stc) return print_error("Memory allocation failed");

    int file = open(av[1], O_RDONLY);
    if (file == -1) {
        free_all_allocate();
        return print_error("Cannot open map file");
    }

    char *line;
    while ((line = get_next_line(file)) != NULL) {
        // printf ("%s",line);
        if (parse_line(stc, line)) {
            free(line);
            close_file(file);            // Directly close file on error
            free_all_allocate();     // Free all allocations on error
            // printf ("lolooooo\n");
            return 1;
        }
        free(line);
    }
    if (stc->c_color->lock != true || stc->f_color->lock != true)
         print_error("color missing yaaa <");
    if (stc->no == NULL || stc->we == NULL || stc->so == NULL || stc->ea == NULL)
         print_error("texture missing yaaa <");
    //...............   map_parse .................//

    if(parse_line_maps (stc) != 0){    return 0;}
    
    fill_maps(stc);
	main2(stc->map_data);
    close_file(file);
    // free_all_allocate();
    return 0;
}