#include "../mandatory/cub3d.h"

 void check_current_positions( map_list_t *tmp, int i)
{
    if (!tmp || !tmp->map)
        return;
        
    if (tmp->map[i + 1] == ' ' || tmp->map[i - 1] == ' ' || !tmp->map[i + 1])
    {
        print_error("Error: Map boundary validation failed - invalid wall configuration");
        exit(1);
    }
    
    if (!tmp->next || tmp->next->length <= i)
    {
        print_error("Error: Map boundary validation failed - invalid map dimensions");
        exit(1);
    }
}

 void check_adjacent_positions( map_list_t *tmp, int i)
{
    if (!tmp || !tmp->prev || !tmp->next || !tmp->prev->map || !tmp->next->map)
        return;
        
    if (tmp->prev->map[i] == ' ' || tmp->prev->map[i] == '\t' || !tmp->prev->map[i])
    {
        print_error("Error: Invalid map - open boundary detected above");
        exit(1);
    }
    
    if (tmp->next->map[i] == ' ' || tmp->next->map[i] == '\t' || !tmp->next->map[i])
    {
        print_error("Error: Invalid map - open boundary detected below");
        exit(1);
    }
}

 int validate_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == '\t' || c == '\n');
}

 int check_zero(map_list_t *tmp)
{
    if (!tmp || !tmp->map)
        return 1;

    for (int i = 0; tmp->map[i]; i++)
    {
        if (ft_isdigit(tmp->map[i]) && tmp->map[i] != '1' && tmp->map[i] != '0')
        {
            print_error("Error: Invalid character in map");
            exit(1);
        }
        
        if (i == 0 && (tmp->map[i] == '0' || tmp->map[tmp->length - 1] != '1'))
        {
            print_error("Error: Map must be enclosed by walls");
            exit(1);
        }
        
        if (tmp->map[i] == '0')
        {
            check_current_positions(tmp, i);
            check_adjacent_positions(tmp, i);
        }
    }
    return 0;
}

 int check_border_line( char *line)
{
    if (!line)
        return 1;
        
    for (int i = 0; line[i]; i++)
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '\t')
        {
            print_error("Error: Border lines must contain only walls and spaces");
            return 1;
        }
    }
    return 0;
}

int parse_line_maps(map_t *stc)
{
    if (!stc || !stc->map_data)
        return 1;

    // First pass: Check for empty lines in map
    map_list_t *tmp = stc->map_data;
    while (tmp)
    {
        if (tmp->next && tmp->map[0] == '\n' && tmp->next->map[0] != '\n')
        {
            print_error("Error: Empty line detected in map");
            return 1;
        }
        if (tmp->map[0] == '\n')
        {
            tmp->prev->next = NULL;
            break;
        }
        tmp = tmp->next;
    }

    // Second pass: Validate map contents
    tmp = stc->map_data;
    while (tmp)
    {
        // Check first/last lines or borders
        
        if (!tmp->prev || !tmp->next || tmp->next->map[0] == '\n')
        {
            if (check_border_line(tmp->map))
                return 1;
        }
        else
        {
            if(tmp->map[tmp->ws] != '1')
            {
                print_error("frist index not wall");
                return 1;
            }
            if (check_zero(tmp))
                return 1;
        }
        tmp = tmp->next;
    }
    if(player_check(stc->map_data)!= 0)
        return 1;
    return 0;
}