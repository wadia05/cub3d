#include "cub3d.h"



int init_ray(cub3d_t *cub) 
{
    
    free(cub->ray);  // Free previous ray if exists
    cub->ray = malloc(sizeof(ray_t) * cub->num_rays);
    if (cub->ray == NULL) {
        return 1;  // Memory allocation failure
    }
    return 0;
}


double dist(float ax, float ay, float bx, float by)
{
    return (sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

double casthorizontal_ray(cub3d_t *cub, double start_angle)
{
    double ray_angle = start_angle;
    double y, x;
    double y_step;
    double x_step;

	if ( ray_angle > 0 && ray_angle < PI)
	{
		y_step = -cub->map_unit;
		y = floor(cub->y / cub->map_unit) * cub->map_unit;
	}
	else
	{
		y_step = cub->map_unit;
		y = floor(cub->y / cub->map_unit) * cub->map_unit + cub->map_unit;
	}
	x_step = cub->map_unit / tan(ray_angle);
	x = cub->x + (cub->y - y) / tan(ray_angle);
	while(cub->map[(int)(x / cub->map_unit)][(int)(y / cub->map_unit)] == '0')
	{
		x += x_step;
		y += y_step;
	}
    cub->ray->rx = x;
    cub->ray->ry = y;
    cub->ray->dist = dist(cub->x, cub->y, x, y);
	cub->ray->is_hori = 1;
    return (cub->ray->dist);
}

double	castvertical_ray(cub3d_t *cub, double start_angle)
{
	double ray_angle = start_angle;
	double	y;
	double	x;
	double y_step = 0;
	double x_step = 0;

	// printf("111\n");
	if ( ray_angle >  3 * P1 && ray_angle < P1)
	{
		x_step = cub->map_unit;
		x = floor(cub->x / cub->map_unit) * cub->map_unit + 64;
	}
	else
	{
		x_step = - cub->map_unit;
		x = floor(cub->x / cub->map_unit) * cub->map_unit ;
	}
	// printf("222\n");

	y = cub->y + (cub->x - x) * tan(ray_angle);
	y_step = x_step * tan(ray_angle);
	int map_x = (int)(x / cub->map_unit);
	int map_y = (int)(y / cub->map_unit);
	while(cub->map[map_x][map_y] != '1')
	{
		cub->ray->rx = x;
		cub->ray->ry = y;
		cub->ray->dist = dist(cub->x, cub->y, x, y);
		cub->ray->is_hori = 0;
		y += y_step;
		x += x_step;
		map_x = (int)(x / cub->map_unit);
		map_y = (int)(y / cub->map_unit);
		if (map_x < 0 || map_x >= 8 || map_y < 0 || map_y >= 8)
	    	break;  // Prevent accessing outside map boundaries
	}
	return (cub->ray->dist);
}

double cast_ray(cub3d_t *cub , double start_angle)
{
	if(start_angle == 0 || start_angle == PI || tan(start_angle) == 0) 
		return (castvertical_ray(cub, start_angle));
	else if(start_angle == P1 || start_angle == 3 * P1)
		return (casthorizontal_ray(cub ,start_angle));
	double distH = casthorizontal_ray(cub ,start_angle);
	double distV = castvertical_ray(cub, start_angle);
	if (distH < distV)
		return (casthorizontal_ray(cub ,start_angle));
	else
		return (castvertical_ray(cub, start_angle));
	return (cub->ray->dist);
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
    int i = - PLAYER_SIZE / 2 ;
    int j = - PLAYER_SIZE / 2 ;
    

    while (i < PLAYER_SIZE / 2)
    {
        j = - PLAYER_SIZE / 2;
        while (j < PLAYER_SIZE / 2)
        {
            mlx_put_pixel(img, x + i, y + j, 0x00FF00FF); // Green color
            j++;
        }
        i++;
    }
    return 0;
}

// int draw(cub3d_t *cub3d)
// {
//     // Safety check for null pointer
//     if (!cub3d || !cub3d->img || !cub3d->map)
//         return (1);

//     // Fill background with black
//     for (int i = 0; i < WIDTH; i++) {
//         for (int j = 0; j < HEIGHT; j++) {
//             mlx_put_pixel(cub3d->img, i, j, 0x000000FF);
//         }
//     }

//     // Draw map elements
//     for (int i = 0; i < cub3d->map_y; i++)  // Notice: using map_y for rows
//     {
//         for (int j = 0; j < cub3d->map_x; j++)  // Notice: using map_x for columns
//         {
//             // Calculate pixel coordinates
//             int x = j * cub3d->map_unit;  // j for x coordinate
//             int y = i * cub3d->map_unit;  // i for y coordinate
            
//             // Bounds checking for pixel coordinates
//             if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
//             {
//                 // Draw walls or empty spaces
//                 if (cub3d->map[i][j] == '1' || cub3d->map[i][j] == '0')
//                 {
//                     uint32_t color = (cub3d->map[i][j] == '1') ? 0x8833FFFF : 0xFFFFFFFF;
                    
//                     // Draw the cell pixel by pixel with bounds checking
//                     for (int px = 0; px < cub3d->map_unit && (x + px) < WIDTH; px++)
//                     {
//                         for (int py = 0; py < cub3d->map_unit && (y + py) < HEIGHT; py++)
//                         {
//                             if ((x + px) >= 0 && (x + px) < WIDTH && 
//                                 (y + py) >= 0 && (y + py) < HEIGHT)
//                             {
//                                 mlx_put_pixel(cub3d->img, x + px, y + py, color);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     draw_plyr(cub3d->img,cub3d->x, cub3d->y, cub3d->angle);
//     return (0);
// }

int check_mov(int x, int y, cub3d_t *cub)
{
    int i;
    int j;
    int map_row;
    int map_col;

    const int BUFFER = 10;

    i = -BUFFER;
    while (i < (PLAYER_SIZE + BUFFER))
    {
        j = -BUFFER;
        while (j < (PLAYER_SIZE + BUFFER))
        {
            map_row = (y + i) / cub->map_unit;
            map_col = (x + j) / cub->map_unit;
            if (map_row >= 0 && map_row < cub->map_y && map_col >= 0 && map_col < cub->map_x) 
            {
                if (cub->map[map_row][map_col] == '1' || cub->map[map_row][map_col] == '3' )
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

cub3d_t	*open_close_door(cub3d_t *cub, int k) 
{
    if(k == 0) // Opening the door
    {
        int i = floor(cub->ray[500].rx / 64);
        int j = floor(cub->ray[500].ry / 64);
        
        // Check if we're looking at a door (usually marked as '3' in the map)
        if(cub->ray[500].is_door == 1)
        {
            cub->map[j][i] = '5'; // Change door state to open
            printf("door opened\n");
            printf("Map value at [%d][%d]: %c\n", i, j, cub->map[j][i]);
            cub->ray[500].is_door = 2;
        }
        else
        {
            printf("i = %d -- j = %d for open is not door\n", i, j);
        }
    }
    else if(k == 1) // Closing the door
    {
        int i = floor(cub->ray[500].rx / 64);
        int j = floor(cub->ray[500].ry / 64);
        
        if(cub->ray[500].is_door == 2)
        {
            cub->map[j][i] = '3'; // Change door state back to closed
            printf("door closed\n");
            cub->ray[500].is_door = 1;
        }
        else
        {
            printf("for close is not door\n");
        }
    }
	return (cub);
}
// void	
// void	open_close_door(cub3d_t *cub, int k)
// {
// 	if(k == 0)
// 	{
// 		int i = floor(cub->ray[500].rx / 64);
// 		int j = floor(cub->ray[500].ry / 64);
// 		if(cub->ray[500].is_door == 1 )
// 		{
// 	 		cub->map[i][j] = '1';
// 			printf("door opened\n");
// 			printf("%c\n",cub->map[i][j] );
// 			cub->ray[500].is_door = 2;
// 		}
// 		else
// 		{

// 			printf("i = %d -- j = %dfor open is not door\n", i , j);
// 		}
// 	}
// 	else if(k == 1)
// 	{
// 		int i = floor(cub->ray[500].rx / 64);
// 		int j = floor(cub->ray[500].ry / 64);
// 		if(cub->ray[500].is_door == 2 )
// 		{
// 	 		cub->map[i][j] = '3';
// 			printf("door closed\n");
// 		}
// 		else
// 			printf("for close is not door\n");
// 	}

// }
void print_all_map(cub3d_t *cub)
{
	int j = 0;
	while(cub->map[18][j] && j < 20)
	{
		printf("%c", cub->map[18][j]);
		j++;
	}
}
void ft_hook(void* param)
{
    cub3d_t* cub3d = param;
    float speed = 10.0f;  // Player movement speed
    float rotation_speed = 0.05f;  // Player rotation speed
    int check;
    float x = cub3d->x;
    float y = cub3d->y;
    float f;

    if (mlx_is_key_down(cub3d->win, MLX_KEY_ESCAPE))
	{
		mlx_terminate(cub3d->win);
		free(cub3d->ray);
		free(cub3d);
        mlx_close_window(cub3d->win);
	}
    if (mlx_is_key_down(cub3d->win, MLX_KEY_W))
    {
        x += cos(cub3d->angle) * speed;
        y += sin(cub3d->angle) * speed;
    }
    if (mlx_is_key_down(cub3d->win, MLX_KEY_S))
    {
        x -= cos(cub3d->angle) * speed;
        y -= sin(cub3d->angle) * speed;
    }
    if (mlx_is_key_down(cub3d->win, MLX_KEY_D))
    {
        f = cub3d->angle + P1;
        x += cos(f) * speed;
        y += sin(f) * speed;

    }
    if (mlx_is_key_down(cub3d->win, MLX_KEY_A))
    {
        f = cub3d->angle + P1;
        x -= cos(f) * speed;
        y -= sin(f) * speed;

    }
    if (mlx_is_key_down(cub3d->win, MLX_KEY_LEFT))
    {
        cub3d->angle -= rotation_speed;
        if (cub3d->angle < 0)
            cub3d->angle += 2 * PI;
        cub3d->xdx = cos(cub3d->angle) * speed;
        cub3d->ydy = sin(cub3d->angle) * speed;
    }

    if (mlx_is_key_down(cub3d->win, MLX_KEY_RIGHT))
    {
        cub3d->angle += rotation_speed;
        if (cub3d->angle > 2 * PI)
            cub3d->angle -= 2 * PI;
        cub3d->xdx = cos(cub3d->angle) * speed;
        cub3d->ydy = sin(cub3d->angle) * speed;
    }
	if (mlx_is_key_down(cub3d->win, MLX_KEY_O))
	{
		cub3d = open_close_door(cub3d, 0);
		print_all_map(cub3d);
	}
	if (mlx_is_key_down(cub3d->win, MLX_KEY_C))
	{
		cub3d = open_close_door(cub3d, 1);
	}
    check = check_mov(x , y, cub3d);
    if(check == 0)
    {
        cub3d->x = x;
        cub3d->y = y;
    }
    draw_rays(cub3d);
}

void init_player(cub3d_t *cub)
{
	int y;
	int x;
	y = 0;	
	while (y < cub->map_y) 
	{
		x = 0;
	    while (x < cub->map_x && cub->map[y][x])
		{
			if(cub->map[y][x] != '0' && cub->map[y][x] != '1' && cub->map[y][x] != ' ' && cub->map[y][x] != '\t' && cub->map[y][x] != '3' && cub->map[y][x] != '5')
			{
		        if (cub->map[y][x] == 'W') 
		            cub->angle = PI;
				else if (cub->map[y][x] == 'N')
					cub->angle = 3 * P1;
				else if (cub->map[y][x] == 'S')
					cub->angle = P1;
				else if (cub->map[y][x] == 'E')
					cub->angle = 0.0;
				cub->x = x * cub->map_unit + cub->map_unit / 2;
		        cub->y = y * cub->map_unit + cub->map_unit / 2;
				// printf("x =%d y = %d\n", x, y);
				cub->map[y][x] = '0';
			}
	        x++;
	    }
		y++;
	}
	return ;
}

void main2(map_list_t *stc, map_t *color)
{
	cub3d_t *cub3d = malloc(sizeof(cub3d_t));
	if (!cub3d)
	    return;

	cub3d->ray = malloc(sizeof(ray_t) * cub3d->num_rays);
	if (!cub3d->ray)
	    return;
    cub3d->info = color;
    loading_image(color);
	if (stc->width_x > stc->high_y)
	{
		cub3d->map_unit = 64;
		stc->ws = stc->width_x;
	}
	else
	{
		cub3d->map_unit = 64;
		stc->ws = stc->high_y;
	}
	cub3d->ray_dof_max = stc->ws;
	cub3d->map_x = stc->width_x;
	cub3d->map_y = stc->high_y;
	cub3d->fov = 60;

	// Initialize map
	map_list_t *current = stc;
	// int i = 0;
	// while(current)
	// {
	// 	printf("%s\n", current->map);
	// 	current = current->next;
	// }
	// exit(1);
	cub3d->map = malloc(sizeof(char *) * stc->high_y);
	if (!cub3d->map)
	    return;

	for (int i = 0; i < stc->high_y; i++)
	{
	    cub3d->map[i] = malloc(sizeof(char) * (stc->width_x + 1)); // +1 for null terminator
	    if (!cub3d->map[i])
	        return;
	    ft_memset((void *)cub3d->map[i], 0, stc->width_x + 1); // Initialize including null terminator
	}

	int j = 0;
	while (current)
	{
	    for (int i = 0; i < stc->width_x && current->map[i]; i++)
	    {
	        cub3d->map[j][i] = current->map[i];
	    }
	    j++;
	    current = current->next;
	}
	init_player(cub3d);
	cub3d->num_rays = 1024;
    cub3d->pa = 0.0;
    cub3d->xdx = cos(cub3d->angle) * 5;
    cub3d->ydy = sin(cub3d->angle) * 5;

    cub3d->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    if (!cub3d->win)
    {
        free(cub3d);
        return ;
    }

    cub3d->img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
    if (!cub3d->img)
    {
        mlx_terminate(cub3d->win);
        free(cub3d);
        return ;
    }

    if (mlx_image_to_window(cub3d->win, cub3d->img, 0, 0) < 0)
    {
        mlx_delete_image(cub3d->win, cub3d->img);
        mlx_terminate(cub3d->win);
        free(cub3d);
        return ;
    }

    mlx_loop_hook(cub3d->win, ft_hook, cub3d);
    mlx_loop(cub3d->win);
    mlx_delete_image(cub3d->win, cub3d->img);
    mlx_terminate(cub3d->win);
    free(cub3d);
	free(cub3d->ray);
    return ;
}
