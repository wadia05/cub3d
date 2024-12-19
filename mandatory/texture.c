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
    float distance_threshold = 1.5f * cub->map_unit;

    // Distance Culling: Check if the wall is within rendering threshold
    if (ray->dist <= distance_threshold) {
        ;
    }
    // Projection plane calculations
    float fov = PI / 3;  // 60-degree field of view
    float dist_project_plane = (WIDTH / 2) / tan(fov / 2);

    // Correct for fisheye distortion
    float corrected_distance = ray->dist * cos(cub->angle - s_agl);

    // Calculate wall strip height based on corrected distance
    float wall_strip_height = (cub->map_unit / corrected_distance) * dist_project_plane;

    // Calculate the starting and ending y-coordinates of the wall strip
    int wall_top = (HEIGHT / 2) - (wall_strip_height / 2);
    int wall_bottom = (HEIGHT / 2) + (wall_strip_height / 2);

    // Clamp wall_top and wall_bottom to stay within the screen bounds
    wall_top = fmax(0, wall_top);
    wall_bottom = fmin(wall_bottom, HEIGHT - 1);

    // Determine which texture to use based on wall orientation and angle
    mlx_texture_t *wall_texture = NULL;
    float texture_x = 0;

    // Select texture based on wall orientation and viewing angle
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
    if (!ray->is_hori) {
        texture_x = fmod(ray->rx, cub->map_unit) / cub->map_unit;
    } else {
        texture_x = fmod(ray->ry, cub->map_unit) / cub->map_unit;
    }

    // Calculate the texture x-coordinate pixel
    int tex_x = (int)(texture_x * wall_texture->width);

    // Render ceiling
    printf ("--->%f,",corrected_distance);
    for (int y = 0; y < wall_top; y++) {
        // Parse ceiling color
        uint32_t ceiling_color = 0;
        if (cub->info->c_color) {
            ceiling_color = (cub->info->c_color->r << 24) | 
                            (cub->info->c_color->g << 16) | 
                            (cub->info->c_color->b << 8) | 
                            0xFF;
        }
        mlx_put_pixel(cub->img, ray_index, y, ceiling_color);
    }

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

        // Convert to 32-bit color with optional distance shading
        float shade_factor = 1.0f - (corrected_distance / (cub->map_unit * 10.0f));
        shade_factor = fmaxf(0.1f, fminf(shade_factor, 1.0f));

        uint32_t color = (
            (uint8_t)(r * shade_factor) << 24 | 
            (uint8_t)(g * shade_factor) << 16 | 
            (uint8_t)(b * shade_factor) << 8 | 
            a
        );

        // Draw the pixel
        mlx_put_pixel(cub->img, ray_index, y, color);
    }

    // Render floor
    for (int y = wall_bottom + 1; y < HEIGHT; y++) {
        // Parse floor color
        uint32_t floor_color = 0;
        if (cub->info->f_color) {
            floor_color = (cub->info->f_color->r << 24) | 
                          (cub->info->f_color->g << 16) | 
                          (cub->info->f_color->b << 8) | 
                          0xFF;
        }
        mlx_put_pixel(cub->img, ray_index, y, floor_color);
    }
}