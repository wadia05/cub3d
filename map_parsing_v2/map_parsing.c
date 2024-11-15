#include "../mandatory/cub3d.h"
int maps_line(map_t *stc, char *line)
{
    

}
int parse_line_maps(map_t *stc, char *file_path)
{
    int file = open(file_path, O_RDONLY);
    if (file == -1) {
        free_all_allocate();
        return print_error("Cannot open map file");
    }
    char *line;
    while ((line = get_next_line(file)) != NULL) {
        if (maps_line(stc, line)) {
            free(line);
            close(file);            // Directly close file on error
            free_all_allocate();     // Free all allocations on error
            // printf ("lolooooo\n");
            return 1;
        }
        free(line);
    }


    return 0;
}