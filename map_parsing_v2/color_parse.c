#include "../mandatory/cub3d.h"

int is_validenum(char *num) {
    int i = 0;
    // Skip leading spaces and tabs
    while (num[i] == ' ' || num[i] == '\t') {
        i++;
    }
    // Check if the remaining string is a valid number
    if (num[i] == '\0') // Ensure there are characters left
        return 1;

    while (num[i] != '\0') {
        if (!ft_isdigit(num[i]))
            return 1;
        i++;
    }
    return 0;
}

int parse_color(char *line,color_t *color) {


    int i = 0;
    // printf("%s\n", line);
    // Find the first digit position in the input line
    if(color->lock == true)
        return print_error ("color duplaicated");
    while (line[i] != '\0') {
        if (ft_isdigit(line[i]))
            break;
        i++;
    }
    if (color_erorr(line) != 0)
        return 1;
    char **color_ = ft_split(&line[i], ',');
    if (color_ == NULL) {
        return 1;
    }

    // Check each color component and ensure it is a valid number
    for (i = 0; color_[i] != NULL; i++) {
        trim_end(color_[i]);
        // printf("color_[%d]: %s\n", i, color_[i]);
        if (is_validenum(color_[i])) {
            printf("Invalid color value at index %d\n", i);
            // Free memory before returning
            free_split(color_);
            return 1;
        }
    }
    color->r = ft_atoi(color_[0]);
    color->g = ft_atoi(color_[1]);
    color->b = ft_atoi(color_[2]);
    color->lock = true;
    free_split(color_);

    if(in_color_range(color) != 0)
        return 1;
    // Free allocated memory after validation
    // free(color_);
    
    printf("line : %s\n", line);
    return 0;
}

int validate_texture_path(char *path, char *name)
{
    // char *path_ = ft_strtrim(path, " \t");/
    
    if (open(path, O_RDONLY) == -1)
    {
        print_error(name);
        print_error(" path not valid\n");
        return (1);
    }
    return 0;
}
