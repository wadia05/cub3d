// #include "cub3d.h"

// typedef struct cub3d_s
// {
//     int x;
//     int y;
//     int map[8][8];
//     int map_x;
//     int map_y;
//     int map_unit;
//     mlx_t *win;
//     mlx_image_t *img;
// } cub3d_t;

// int draw_moraba3(int x, int y, int color, cub3d_t *cub)
// {
//     int i = 0;
//     int j;
//     while (i < cub->map_unit)
//     {
//         j = 0;
//         while(j < cub->map_unit)
//         {
//             mlx_put_pixel(cub->img, x+i, y+j, color);
//             j++;
//         }
//         i++;
//     }
//     return 0;
// }

// int draw_plyr(mlx_image_t *img, int x, int y)
// {
//     int i = 0;
//     int j = 0;
//     while (i < 4)
//     {
//         j = 0;
//         while (j < 4)
//         {
//             mlx_put_pixel(img, x + i, y + j, 0x00FF00FF);
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }

// int draw(cub3d_t *cub3d)
// {
//     int x;
//     int y = 0;
    
//     // Clear the image
//     for (int i = 0; i < WIDTH; i++)
//         for (int j = 0; j < HEIGHT; j++)
//             mlx_put_pixel(cub3d->img, i, j, 0x000000FF);
    
//     // Draw map
//     while (y < cub3d->map_y)
//     {
//         x = 0;
//         while (x < cub3d->map_x)
//         {
//             if(cub3d->map[y][x] == 1)
//             {
//                 draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0x990022FF, cub3d);
//             }
//             else
//                 draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0x002d44FF, cub3d);
//             x++;
//         }
//         y++;
//     }
    
//     // Draw player
//     draw_plyr(cub3d->img, cub3d->x, cub3d->y);
//     return (0);
// }

// void ft_hook(void* param)
// {
//     cub3d_t* cub3d = param;
    
//     if (mlx_is_key_down(cub3d->win, MLX_KEY_ESCAPE))
//         mlx_close_window(cub3d->win);
    
//     if (mlx_is_key_down(cub3d->win, MLX_KEY_UP))
//         cub3d->y -= 4;
//     if (mlx_is_key_down(cub3d->win, MLX_KEY_DOWN))
//         cub3d->y += 4;
//     if (mlx_is_key_down(cub3d->win, MLX_KEY_LEFT))
//         cub3d->x -= 4;
//     if (mlx_is_key_down(cub3d->win, MLX_KEY_RIGHT))
//         cub3d->x += 4;
    
//     draw(cub3d);
// }

// int main()
// {
//     cub3d_t *cub3d;
    
//     cub3d = malloc(sizeof(cub3d_t));
//     if (cub3d == NULL)
//         return (1);
    
//     cub3d->map_unit = 64;
//     cub3d->map_x = 8;
//     cub3d->map_y = 8;
    
//     // Initialize map
//     int initial_map[8][8] = {
//         {1,1,1,1,1,1,1,1},
//         {1,0,0,0,1,0,0,1},
//         {1,0,0,0,1,0,0,1},
//         {1,0,0,0,1,0,0,1},
//         {1,0,0,0,0,0,0,1},
//         {1,0,1,1,1,0,0,1},
//         {1,0,0,0,0,0,0,1},
//         {1,1,1,1,1,1,1,1}
//     };
    
//     // Copy the initial map to cub3d->map
//     for (int i = 0; i < 8; i++)
//         for (int j = 0; j < 8; j++)
//             cub3d->map[i][j] = initial_map[i][j];
    
//     cub3d->x = 100;
//     cub3d->y = 100;
    
//     cub3d->win = mlx_init(WIDTH, HEIGHT, "cub3d", true);
//     if (!cub3d->win)
//     {
//         free(cub3d);
//         return (1);
//     }
    
//     cub3d->img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
//     if (!cub3d->img)
//     {
//         mlx_terminate(cub3d->win);
//         free(cub3d);
//         return (1);
//     }
    
//     if (mlx_image_to_window(cub3d->win, cub3d->img, 0, 0) < 0)
//     {
//         mlx_delete_image(cub3d->win, cub3d->img);
//         mlx_terminate(cub3d->win);
//         free(cub3d);
//         return (1);
//     }
    
//     mlx_loop_hook(cub3d->win, ft_hook, cub3d);
//     mlx_loop(cub3d->win);
    
//     // Cleanup
//     mlx_delete_image(cub3d->win, cub3d->img);
//     mlx_terminate(cub3d->win);
//     free(cub3d);
    
//     return (0);
// }