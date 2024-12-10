#include "../mandatory/cub3d.h"

void trim_end(char *str)
{
    int len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
    {
        str[len - 1] = '\0';
        len--;
    }
}

int check_frist_last(char *line)
{
    int i  = 0;
    while (line[i] != '\0')
    {
        // write(1, "hello\n", 6);
        if (line[i] != '1'  && line[i] != ' ' && line[i] != '\t')
        { 
            free(line);
            free_all_axllocate();
            print_error("error frist and last line should be just");
            write (1,"2\n", 2);
            exit(1);
        }
        i++;
    }
    return 0;
}

void check_current_position(map_list_t *tmp, int i)
{
    if (tmp->map[i+1] == ' ' || tmp->map[i-1] == ' ' || tmp->map[i+1] == '\0')
    { 
        print_error("player will go out 0");
        exit(1);
    }
    if (tmp->next->length < i)
    { 
        print_error("player will go out 1");
        exit(1);
    }
}

void check_adjacent_positions(map_list_t *tmp, int i)
{
    if(tmp->prev->map[i] == ' ' || tmp->prev->map[i] == '\t' || tmp->prev->map[i] == '\0')
    {
        print_error("player will go out 3");
        exit(1);
    }
    if(tmp->next->map[i] == ' ' || tmp->next->map[i] == '\t' || tmp->next->map[i] == '\0')
    {
        print_error("player will go out 4");
        exit(1);
    }
}
int check_zero(map_list_t *hd)
{
    map_list_t *tmp = hd;
    int i = 0;
    while (tmp->map[i] != '\0')
    {
        if (ft_isdigit(tmp->map[i]) != 0)
        {
            if (tmp->map[i] != '1' && tmp->map[i] != '0')
            {
                print_error("map number not valid\n");
                exit(1);
            }
        }
        if (i == 0 && (tmp->map[i] == '0' || tmp->map[tmp->length-1] != '1'))
        {
            write(1, "lol\n", 4);
            print_error("wtf are u doing is not wall\n");
            exit(1);
        }
        if (tmp->map[i] == '0')
        {
            check_current_position(tmp, i);
            check_adjacent_positions(tmp, i);
        }
        i++;
    }
    return 0;
}
int map_check(map_list_t *hd)
{
    map_list_t *tmp = hd;
    while (tmp != NULL)
    {
        if(tmp->prev == NULL || tmp->next == NULL)
        {
            // print_error(tmp->map);
            // write(1,"\n",1);
            if (check_frist_last(tmp->map) == 1)
                return 1;
            tmp = tmp->next;
            continue;
        }
        // write(1, "hello\n", 6);
        check_zero(tmp);
        tmp = tmp->next;
    }

    return 0;
}

int white_space(char *map)
{
    int i= 0;
    while (map[i] == ' ' || map[i] == '\t')
        i++;
    return i;
}

map_list_t *create_map_list(char *map)
{
    map_list_t *new = tracker_malloc(sizeof(map_list_t));
    if (new == NULL)
        return (NULL);
    trim_end(map);
    new->map = ft_strdup(map);
    new->length = ft_strlen(map);
    new->ws = white_space(map);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}
map_list_t *add_map_list(map_list_t *head, char *map)
{
    map_list_t *new = create_map_list(map);
    if (new == NULL)
        return (NULL);
    if (head == NULL)
        return (new);
    map_list_t *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return (head);
}
int parse_map(int file, map_t *stc)
{
    (void)stc;
    char *line = NULL;
    line = get_next_line(file);

    while (line != NULL)
    {
        remove_newline(line);
        stc->map_data = add_map_list(stc->map_data, line);
        free(line);
        line = get_next_line(file);
    }
    free(line);
    map_list_t *tmp = stc->map_data;
    map_check(tmp);

    printf("map_was_good yaaaaay\n");
    tmp = stc->map_data;
    player_check(tmp);


    return (0);
}