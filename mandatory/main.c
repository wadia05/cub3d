#include "cub3d.h"

typedef struct ray_s
{
    //--------- horizontal -----------
    int r;                  // Ray counter
    int mx, my, mp;         // Map grid coordinates and position
    int dof;                // Depth of field
    float rx, ry;           // Ray position
    float ra;               // Ray angle
    float xo, yo;           // X and Y offsets
    float aTan; 

    //--------- vertitcal -----------
    float vtan;
    float distH;
    float xH;
    float yH;
    float distV;
    float dist;
    float xV;
    float yV;


} ray_t;

typedef struct cub3d_s
{
    float x;         // Player's x-coordinate
    float y;         // Player's y-coordinate
    float xdx;       // Player's direction vector x-component
    float ydy;       // Player's direction vector y-component
    float angle;     // Player's current angle

    int map[8][8];   // 2D map (walls and empty spaces)
    int map_x;       // Number of columns in the map
    int map_y;       // Number of rows in the map
    int map_unit;    // Size of each square in the map (e.g., 64)

    float pa;
    int fov;         // Field of view (e.g., 60 degrees)
    int num_rays;    // Number of rays to cast (e.g., 60)
    ray_t *ray;
    mlx_t *win;      // MiniLibX window
    mlx_image_t *img; // MiniLibX image to draw on
} cub3d_t;

float dist(float ax, float ay, float bx, float by){
    return (sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int draw_rays(cub3d_t *cub)
{
    free(cub->ray);  // Free previous ray if exists
    cub->ray = malloc(sizeof(ray_t));
    if (cub->ray == NULL)
        return 1;
    ray_t *rays = cub->ray;
    rays->distH = 10000000;
    rays->distV = 10000000;
    rays->xH = cub->x;
    rays->yH = cub->y;
    rays->xV = cub->x;
    rays->yV = cub->y;
    int i = -1;
    float start_angle = cub->angle - (DR*30);
    if (start_angle < 0) 
        start_angle += 2 * PI;
    if (start_angle > 2 * PI)
        start_angle -= 2 * PI;
        // float RD = 
    while (++i < cub->num_rays)
    {  
        rays->dof = 0;
        rays->aTan = -1.0 / tan(start_angle);
        
        // Handle horizontal lines
        if (start_angle > PI)
        {
            rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.0001;
            rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
            rays->yo = -cub->map_unit;  
            rays->xo = -rays->yo * rays->aTan;
        }
        else if (start_angle < PI)
        {
            rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit + cub->map_unit;
            rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
            rays->yo = cub->map_unit;  
            rays->xo = -rays->yo * rays->aTan;
        }
        else
        {
            rays->xH = cub->x;
            rays->yH = cub->y;
            rays->dof = 8;
        }

        // Check horizontal intersections
        while (rays->dof < 8)
        {
            int mx = (int)(rays->xH) / cub->map_unit;
            int my = (int)(rays->yH) / cub->map_unit;
            
            if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
            {
                if (cub->map[my][mx] == 1)
                {
                    rays->dof = 8;
                }
                else
                {
                    rays->xH += rays->xo;
                    rays->yH += rays->yo;
                    rays->dof += 1;
                }
            }
            else
            {
                rays->dof = 8;
            }
        }
        
        // Handle vertical lines
        rays->dof = 0;
        rays->aTan = -tan(start_angle);  // Changed from vtan to aTan for clarity
        if (start_angle > P1 && start_angle < P2)
        {
            rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit - 0.0001;
            rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;  // Fixed: Changed yH to yV
            rays->xo = -cub->map_unit;  
            rays->yo = -rays->xo * rays->aTan;
        }
        else if (start_angle < P1 || start_angle > P2)
        {
            rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit + cub->map_unit;
            rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;  // Fixed: Changed yH to yV
            rays->xo = cub->map_unit;  
            rays->yo = -rays->xo * rays->aTan;
        }
        else
        {
            rays->xV = cub->x;
            rays->yV = cub->y;  // Fixed: Changed yH to yV
            rays->dof = 8;
        }

        // Check vertical intersections
        while (rays->dof < 8)
        {
            int mx = (int)(rays->xV) / cub->map_unit;
            int my = (int)(rays->yV) / cub->map_unit;
            
            if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
            {
                if (cub->map[my][mx] == 1)
                {
                    rays->dof = 8;
                }
                else
                {
                    rays->xV += rays->xo;
                    rays->yV += rays->yo;
                    rays->dof += 1;
                }
            }
            else
            {
                rays->dof = 8;
            }
        }

        // Calculate distances and choose shorter ray
        double distH = dist(cub->x, cub->y, rays->xH, rays->yH);
        double distV = dist(cub->x, cub->y, rays->xV, rays->yV);
        
        if (distH < distV)
        {
            rays->rx = rays->xH;
            rays->ry = rays->yH;
            rays->dist = distH;
            draw_line(cub->img, (int)cub->x + 2, (int)cub->y + 2, (int)rays->rx, (int)rays->ry, 0xFFFF00FF);
        }
        else
        {
            rays->rx = rays->xV;
            rays->ry = rays->yV;
            rays->dist = distV;
            draw_line(cub->img, (int)cub->x + 2, (int)cub->y + 2, (int)rays->rx, (int)rays->ry, 0xFF4500FF);
        }
        start_angle += DR;
            if (start_angle < 0)
        start_angle += 2 * PI;
            if (start_angle > 2 * PI)
        start_angle -= 2 * PI;
        
    }
    return 0;
}
int draw_moraba3(int x, int y, int color, cub3d_t *cub)
{
    int i = 0;
    int j;
    
    // Reduce the size of each cube by 1 pixel to create a gap
    int cube_size = cub->map_unit - 1;
    
    while (i < cube_size)
    {
        j = 0;
        while(j < cube_size)
        {
            mlx_put_pixel(cub->img, x+i, y+j, color);
            j++;
        }
        i++;
    }
    return 0;
}
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        mlx_put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

int draw_plyr(mlx_image_t *img, int x, int y, float angle)
{
    int i = 0;
    int j = 0;
    
    // Draw 4x4 pixel square for the player
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            mlx_put_pixel(img, x + i, y + j, 0x00FF00FF); // Green color
            j++;
        }
        i++;
    }

    // Set the length of the direction line
    int line_length = 20;

    // Calculate the end point of the direction line
    int x_end = x + 2 + (int)(line_length * cos(angle)); // x + 2 to start from the center of the player
    int y_end = y + 2 + (int)(line_length * sin(angle)); // y + 2 to start from the center of the player

    // Draw the direction line (white color)
    draw_line(img, x + 2, y + 2, x_end, y_end, 0xFFFFFFFF);

    return 0;
}

int draw(cub3d_t *cub3d)
{
    int x;
    int y = 0;
    
    // Clear the image
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            mlx_put_pixel(cub3d->img, i, j, 0x000000FF);
    
    // Draw map
    while (y < cub3d->map_y)
    {
        x = 0;
        while (x < cub3d->map_x)
        {
            if(cub3d->map[y][x] == 1)
            {
                draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0x990022FF, cub3d);
            }
            else
                draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0x002d44FF, cub3d);
            x++;
        }
        y++;
    }
    
    // Draw player
    draw_plyr(cub3d->img, cub3d->x, cub3d->y, cub3d->angle);
    return (0);
}

void ft_hook(void* param)
{
    cub3d_t* cub3d = param;
    float speed = 2.0f;  // Player movement speed
    float rotation_speed = 0.05f;  // Player rotation speed

    // Close window if escape key is pressed
    if (mlx_is_key_down(cub3d->win, MLX_KEY_ESCAPE))
        mlx_close_window(cub3d->win);

    // Move forward
    if (mlx_is_key_down(cub3d->win, MLX_KEY_UP))
    {
        cub3d->x += cos(cub3d->angle) * speed;
        cub3d->y += sin(cub3d->angle) * speed;
		printf("x :%f y :%f angle :%f\n", cub3d->x, cub3d->y,cub3d->angle);
    }

    // Move backward
    if (mlx_is_key_down(cub3d->win, MLX_KEY_DOWN))
    {
        cub3d->x -= cos(cub3d->angle) * speed;
        cub3d->y -= sin(cub3d->angle) * speed;

    }
    // Rotate left (counter-clockwise)
    if (mlx_is_key_down(cub3d->win, MLX_KEY_LEFT))
    {
        cub3d->angle -= rotation_speed;
        if (cub3d->angle < 0)
            cub3d->angle += 2 * PI;

        // Update direction vectors after rotation
        cub3d->xdx = cos(cub3d->angle) * speed;
        cub3d->ydy = sin(cub3d->angle) * speed;
    }

    // Rotate right (clockwise)
    if (mlx_is_key_down(cub3d->win, MLX_KEY_RIGHT))
    {
        cub3d->angle += rotation_speed;
        if (cub3d->angle > 2 * PI)
            cub3d->angle -= 2 * PI;

        // Update direction vectors after rotation
        cub3d->xdx = cos(cub3d->angle) * speed;
        cub3d->ydy = sin(cub3d->angle) * speed;
    }

    // Redraw the scene after movement/rotation
    draw(cub3d);
    draw_rays(cub3d);
}

int main()
{
    cub3d_t *cub3d;

    cub3d = malloc(sizeof(cub3d_t));
    if (cub3d == NULL)
        return (1);

    cub3d->map_unit = 64;
    cub3d->map_x = 8;
    cub3d->map_y = 8;
    cub3d->num_rays = 60;
    cub3d->fov = 60;


    // Initialize map
    int initial_map[8][8] = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };

    // Copy the initial map to cub3d->map
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cub3d->map[i][j] = initial_map[i][j];

    cub3d->x = 100.0;
    cub3d->y = 100.0;
    cub3d->angle = 0.0;
    cub3d->pa = 0.0;
    cub3d->xdx = cos(cub3d->angle) * 5;
    cub3d->ydy = sin(cub3d->angle) * 5;

    cub3d->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    if (!cub3d->win)
    {
        free(cub3d);
        return (1);
    }

    cub3d->img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
    if (!cub3d->img)
    {
        mlx_terminate(cub3d->win);
        free(cub3d);
        return (1);
    }

    if (mlx_image_to_window(cub3d->win, cub3d->img, 0, 0) < 0)
    {
        mlx_delete_image(cub3d->win, cub3d->img);
        mlx_terminate(cub3d->win);
        free(cub3d);
        return (1);
    }

    mlx_loop_hook(cub3d->win, ft_hook, cub3d);
    mlx_loop(cub3d->win);

    // Cleanup
    mlx_delete_image(cub3d->win, cub3d->img);
    mlx_terminate(cub3d->win);
    free(cub3d);

    return (0);
}
