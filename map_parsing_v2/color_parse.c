#include "../mandatory/cub3d.h"

int is_validenum(char *num)
{
    int i = 0;
    
    while (num[i] == ' ' || num[i] == '\t')
        i++;
    
    if (num[i] == '\0')
        return 1;
        
    while (num[i] != '\0')
    {
        if (!ft_isdigit(num[i]))
            return 1;
        i++;
    }
    return 0;
}

char **isvalide_color_line(char *line)
{
    int i = 0;
    char **color_;
    
    while (line[i] != '\0')
    {
        if (ft_isdigit(line[i]))
            break;
        i++;
    }
    
    if (color_erorr(line) != 0)
        return NULL;
        
    color_ = ft_split(&line[i], ',');
    if (color_ == NULL)
        return NULL;
    
    i = 0;
    while (color_[i] != NULL)
    {
        trim_end(color_[i]);
        if (is_validenum(color_[i]))
        {
            printf("Invalid color value at index %d\n", i);
            free_split(color_);
            return NULL;
        }
        i++;
    }
    
    return color_;
}

int parse_color(char *line, color_t *color)
{
    char **color_;
    
    if (color->lock == true)
        return print_error("color duplicated");
        
    color_ = isvalide_color_line(line);
    if (color_ == NULL)
        return 1;
        
    if (color_[0] == NULL || color_[1] == NULL || color_[2] == NULL)
    {
        free_split(color_);
        print_error("Invalid color values");
        return 1;
    }
    color->r = ft_atoi(color_[0]);
    color->g = ft_atoi(color_[1]);
    color->b = ft_atoi(color_[2]);
    color->lock = true;
    free_split(color_);
    if (in_color_range(color) != 0)
        return 1;
        
    return 0;
}

int validate_texture_path(char *path, char *name)
{
    if (open(path, O_RDONLY) == -1)
    {
        print_error(name);
        print_error(" path not valid\n");
        return 1;
    }
    return 0;
}
