#include "../mandatory/cub3d.h"
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
