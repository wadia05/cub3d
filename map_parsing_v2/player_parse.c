#include "../mandatory/cub3d.h"

int is_valid_alpha(char alpha)
{
    if (alpha == 'E' || alpha == 'S' || alpha == 'W' || alpha == 'N')
    {
        return 0;
    }
    else 
    {
        print_error("alpha error not valid\n");
        return 1;
    }
}

int find_player(map_list_t *ply)
{
    int i = 0;
    int ply_offset = 0;

    while (ply->map[i] != '\0')
    {
        if (ply->map[i] == '1' || ply->map[i] == '0' || ply->map[i] == ' ' || ply->map[i] == '\t')
        {
            i++;
            continue;
        }

        if (ply->map[i] >= 'A' && ply->map[i] <= 'Z')
        {
            // print_error(ply->map);
            // write(1, "\n", 1);
            if (is_valid_alpha(ply->map[i]) != 0)
                free_at_exit();
            check_current_positions(ply, i);
            check_adjacent_positions(ply , i);
            ply_offset++;
        }
        else
        {
            print_error("player character wrong 'W E S N'\n");
            free_at_exit();
            // exit(1);
        }
        i++;
    }
    return ply_offset;
}
int player_check(map_list_t *hd)
{
    map_list_t *tmp = hd;
    int ply_offset = 0;

    while (tmp != NULL)
    {
        ply_offset += find_player(tmp);
        if (ply_offset > 1)
        {
            print_error("too many players in map");
            free_at_exit();
            // exit(1);
        }
        tmp = tmp->next;
    }

    if (ply_offset == 0)
    {
        print_error("no player in map\n");
        free_at_exit();
        // exit(1);
    }

    return 0;
}