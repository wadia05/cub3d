#include "cub3d.h"
void loading_image(map_t *mp)
{
    mp->no_png = mlx_load_png(mp->no);
    if(!mp->no_png) {
        // printf("Failed to load North texture: %s\n", map->no_path);
        return ;
    }
    mp->so_png = mlx_load_png(mp->so);
    if(!mp->so_png) {
        // printf("Failed to load North texture: %s\n", map->no_path);
        return ;
    }
    mp->ea_png = mlx_load_png(mp->ea);
    if(!mp->ea_png) {
        // printf("Failed to load North texture: %s\n", map->no_path);
        return ;
    }
    mp->we_png = mlx_load_png(mp->we);
    if(!mp->we_png) {
        // printf("Failed to load North texture: %s\n", map->no_path);
        return ;
    }
}

