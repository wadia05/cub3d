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
    printf ("texture loading successfully !!!");
}
void draw_wall(cub3d_t *cub, ray_t *ray, int ray_index, double s_agl)
{
    // Projection plane calculations
    float fov = PI / 3;  // 60-degree field of view
    float dist_project_plane = (WIDTH / 2) / tan(fov / 2);

    // Calculate wall strip height based on ray distance
    float wall_strip_height = (cub->map_unit / ray->dist) * dist_project_plane;

    // Calculate the starting and ending y-coordinates of the wall strip
    int wall_top = (HEIGHT / 2) - (wall_strip_height / 2);
    int wall_bottom = (HEIGHT / 2) + (wall_strip_height / 2);

    // Clamp wall_top and wall_bottom to stay within the screen bounds
    wall_top = fmax(0, wall_top);
    wall_bottom = fmin(wall_bottom, HEIGHT - 1);

    // Determine which texture to use based on wall orientation and angle
    mlx_texture_t *wall_texture = NULL;
    float texture_x = 0;

    if (!ray->is_hori) {
        if (s_agl > 0 && s_agl < PI) {
            wall_texture = cub->info->so_png;  // South wall
        } else {
            wall_texture = cub->info->no_png;  // North wall
        }
    } else {
        if (s_agl > PI/2 && s_agl < 3*PI/2) {
            wall_texture = cub->info->we_png;  // West wall
        } else {
            wall_texture = cub->info->ea_png;  // East wall
        }
    }

    // Calculate the x-coordinate on the texture


    // Calculate the texture x-coordinate pixel
    int tex_x = (int)(texture_x * wall_texture->width);

    // Draw textured wall strip
    for (int y = wall_top; y <= wall_bottom; y++)
    {
        // Calculate the y-coordinate on the texture
        float texture_y = (float)(y - wall_top) / (wall_bottom - wall_top);
        int tex_y = (int)(texture_y * wall_texture->height);

        // Get the color from the texture
        uint8_t r = wall_texture->pixels[(tex_y * wall_texture->width + tex_x) * 4];
        uint8_t g = wall_texture->pixels[(tex_y * wall_texture->width + tex_x) * 4 + 1];
        uint8_t b = wall_texture->pixels[(tex_y * wall_texture->width + tex_x) * 4 + 2];
        uint8_t a = wall_texture->pixels[(tex_y * wall_texture->width + tex_x) * 4 + 3];

        // Convert to 32-bit color
        uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;

        // Draw the pixel
        mlx_put_pixel(cub->img, ray_index, y, color);
    }
}