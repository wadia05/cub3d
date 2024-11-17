#include "../mandatory/cub3d.h"

void free_at_exit()
{
    free_all_allocate();
    exit(1);
}