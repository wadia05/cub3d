#include "cub3d.h"



int init_ray(cub3d_t *cub) 
{
    free(cub->ray);  // Free previous ray if exists
    cub->ray = malloc(sizeof(ray_t));
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
// void draw_rays(cub3d_t *cub)
// {
// 	int i = -1;
// 	// int j = 0;
// 	double start_angle = cub->angle - (DR*30);
// 	if (start_angle < 0) 
// 		start_angle += 2 * PI;
// 	if (start_angle > 2 * PI)
// 		start_angle -= 2 * PI;
// 	while (++i < 25)
// 	{
// 		cast_ray(cub , start_angle);
// 		draw_line(cub->img, (int)cub->x, (int)cub->y, (int)cub->ray->rx, (int)cub->ray->ry, 0xFFFF00FF);
// 		printf("angle == %f", start_angle);
// 		start_angle += DR;
// 		if (start_angle < 0)
// 			start_angle += 2 * PI; 
// 		if (start_angle > 2 * PI)
// 			start_angle -= 2 * PI;
// 	}
// 	return ;
// // }
// int draw_rays(cub3d_t *cub)
// {
//     free(cub->ray);  // Free previous ray if exists
//     cub->ray = malloc(sizeof(ray_t));
//     if (cub->ray == NULL)
//         return 1;
//     ray_t *rays = cub->ray;
//     rays->distH = 10000000;
//     rays->distV = 10000000;
//     rays->xH = cub->x;
//     rays->yH = cub->y;
//     rays->xV = cub->x;
//     rays->yV = cub->y;
//     int i = -1;
//     float start_angle = cub->angle - (DR*30);
//     if (start_angle < 0) 
//         start_angle += 2 * PI;
//     if (start_angle > 2 * PI)
//         start_angle -= 2 * PI;
//         // float RD = 
//     while (++i < cub->num_rays)
//     {  
//         rays->dof = 0;
//         rays->aTan = -1.0 / tan(start_angle);
        
//         // Handle horizontal lines
//         if (start_angle > PI)
//         {
//             rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit - 0.0001;
//             rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
//             rays->yo = -cub->map_unit;  
//             rays->xo = -rays->yo * rays->aTan;
//         }
//         else if (start_angle < PI)
//         {
//             rays->yH = ((int)(cub->y / cub->map_unit)) * cub->map_unit + cub->map_unit;
//             rays->xH = (cub->y - rays->yH) * rays->aTan + cub->x;
//             rays->yo = cub->map_unit;  
//             rays->xo = -rays->yo * rays->aTan;
//         }
//         else
//         {
//             rays->xH = cub->x;
//             rays->yH = cub->y;
//             rays->dof = 8;
//         }

//         // Check horizontal intersections
//         while (rays->dof < 8)
//         {
//             int mx = (int)(rays->xH) / cub->map_unit;
//             int my = (int)(rays->yH) / cub->map_unit;
            
//             if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
//             {
//                 if (cub->map[my][mx] == 1)
//                 {
//                     rays->dof = 8;
//                 }
//                 else
//                 {
//                     rays->xH += rays->xo;
//                     rays->yH += rays->yo;
//                     rays->dof += 1;
//                 }
//             }
//             else
//             {
//                 rays->dof = 8;
//             }
//         }
        
//         // Handle vertical lines
//         rays->dof = 0;
//         rays->aTan = -tan(start_angle);  // Changed from vtan to aTan for clarity
//         if (start_angle > P1 && start_angle < P2)
//         {
//             rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit - 0.0001;
//             rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;  // Fixed: Changed yH to yV
//             rays->xo = -cub->map_unit;  
//             rays->yo = -rays->xo * rays->aTan;
//         }
//         else if (start_angle < P1 || start_angle > P2)
//         {
//             rays->xV = ((int)(cub->x / cub->map_unit)) * cub->map_unit + cub->map_unit;
//             rays->yV = (cub->x - rays->xV) * rays->aTan + cub->y;  // Fixed: Changed yH to yV
//             rays->xo = cub->map_unit;  
//             rays->yo = -rays->xo * rays->aTan;
//         }
//         else
//         {
//             rays->xV = cub->x;
//             rays->yV = cub->y;  // Fixed: Changed yH to yV
//             rays->dof = 8;
//         }

//         // Check vertical intersections
//         while (rays->dof < 8)
//         {
//             int mx = (int)(rays->xV) / cub->map_unit;
//             int my = (int)(rays->yV) / cub->map_unit;
            
//             if (mx >= 0 && mx < cub->map_x && my >= 0 && my < cub->map_y)
//             {
//                 if (cub->map[my][mx] == 1)
//                 {
//                     rays->dof = 8;
//                 }
//                 else
//                 {
//                     rays->xV += rays->xo;
//                     rays->yV += rays->yo;
//                     rays->dof += 1;
//                 }
//             }
//             else
//             {
//                 rays->dof = 8;
//             }
//         }

//         // Calculate distances and choose shorter ray
//         double distH = dist(cub->x, cub->y, rays->xH, rays->yH);
//         double distV = dist(cub->x, cub->y, rays->xV, rays->yV);
        
//         if (distH < distV)
//         {
//             rays->rx = rays->xH;
//             rays->ry = rays->yH;
//             rays->dist = distH;
//             draw_line(cub->img, (int)cub->x + 2, (int)cub->y + 2, (int)rays->rx, (int)rays->ry, 0xFFFF00FF);
//         }
//         else
//         {
//             rays->rx = rays->xV;
//             rays->ry = rays->yV;
//             rays->dist = distV;
//             draw_line(cub->img, (int)cub->x + 2, (int)cub->y + 2, (int)rays->rx, (int)rays->ry, 0xFF4500FF);
//         }
//         start_angle += DR;
//             if (start_angle < 0)
//         start_angle += 2 * PI;
//             if (start_angle > 2 * PI)
//         start_angle -= 2 * PI;
        
//     }
//     return 0;
// }

// void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
// {
// 	float	dx;
// 	float	dy;
// 	int		steps;
// 	float	x_inc;
// 	float	y_inc;
// 	float	x;
// 	float	y;
// 	int		i;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	steps = (fabsf(dx) > fabsf(dy)) ? fabsf(dx) : fabsf(dy);
// 	x_inc = dx / steps;
// 	y_inc = dy / steps;
// 	x = x0;
// 	y = y0;
// 	i = 0;
// 	while (i <= steps)
// 	{
// 		mlx_put_pixel(img, round(x), round(y), color);
// 		x += x_inc;
// 		y += y_inc;
// 		i++;
// 	}
// }
int draw_plyr(mlx_image_t *img, int x, int y, float angle)
{
	// int player_size = 3;
    int i = - PLAYER_SIZE / 2 ;
    int j = - PLAYER_SIZE / 2 ;
    
    // Draw 4x4 pixel square for the player
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

    int line_length = 20;
    for (int i = 0; i < line_length; i++) {
        int rotated_x = x + (  i) * cos((angle ));
        int rotated_y = y + (  i) * sin((angle ) );
        mlx_put_pixel(img, rotated_x, rotated_y, 0xFFFFFFFF); // Draw each pixel of the line
    }
    // draw_line(img, x , y , x_end, y_end, 0xFFFFFFFF);

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
            if(cub3d->map[y][x] == '1')
                draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0xFF0000FF, cub3d);
            if(cub3d->map[y][x] == '0')
				draw_moraba3(x * cub3d->map_unit, y * cub3d->map_unit, 0x002d44FF, cub3d);
            x++;
        }
        y++;
    }
    
    // Draw player
    draw_plyr(cub3d->img, cub3d->x, cub3d->y, cub3d->angle);
    return (0);
}

int check_mov(int x, int y, cub3d_t *cub)
{
    int i;
    int j;

    int map_row;
    int map_col;

    i = 0;
    while(i < PLAYER_SIZE) 
    {
        j = 0;
        while(j < PLAYER_SIZE) 
        {
            map_row = (y  + i) / cub->map_unit;
            map_col = (x  + j) / cub->map_unit;
            if (map_row >= 0 && map_row < cub->map_y  && map_col >= 0 && map_col < cub->map_x) 
            {
                if (cub->map[map_row][map_col] == '1') 
                    return (1);
            }
            j++;
        }
        i++;
    }
    return 0;
}
void ft_hook(void* param)
{
    cub3d_t* cub3d = param;
    float speed = 2.0f;  // Player movement speed
    float rotation_speed = 0.05f;  // Player rotation speed
    int check;
    float x = cub3d->x;
    float y = cub3d->y;
    float f;

    // Close window if escape key is pressed
    if (mlx_is_key_down(cub3d->win, MLX_KEY_ESCAPE))
        mlx_close_window(cub3d->win);

    // Move forward
    if (mlx_is_key_down(cub3d->win, MLX_KEY_W))
    {
        x += cos(cub3d->angle) * speed;
        y += sin(cub3d->angle) * speed;
		// printf("x :%f y :%f angle :%f check %f\n", x, y,cub3d->angle, cub3d->ray->distH);
		// printf("meeeeee%f\n", cub3d->y - (int)(cub3d->y / cub3d->map_unit) * cub3d->map_unit);
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
    check = check_mov(x , y, cub3d);
    if(check == 0)
    {
        cub3d->x = x;
        cub3d->y = y;
    }
    draw(cub3d);
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
	    while (x < cub->map_x)
		{
			if(cub->map[y][x] != '0' && cub->map[y][x] != '1')
			{
		        if (cub->map[y][x] == 'W') 
		            cub->angle = 0.0;
				else if (cub->map[y][x] == 'N')
					cub->angle = P1;
				else if (cub->map[y][x] == 'S')
					cub->angle = 3 * P1;
				else if (cub->map[y][x] == 'E')
					cub->angle = PI;
				cub->x = x * cub->map_unit + cub->map_unit / 2;
		        cub->y = y * cub->map_unit + cub->map_unit / 2;
				cub->map[y][x] = '0';
			}
	        x++;
	    }
		y++;
	}
	return ;
}
void main2(map_list_t *stc)
{
	cub3d_t *cub3d = malloc(sizeof(cub3d_t));
	if (!cub3d)
	    return;

	cub3d->ray = malloc(sizeof(ray_t));
	if (!cub3d->ray)
	    return;
	if (stc->width_x > stc->high_y)
		cub3d->map_unit = HEIGHT / stc->width_x;
	else
		cub3d->map_unit = HEIGHT / stc->high_y;
	cub3d->map_x = stc->width_x;
	cub3d->map_y = stc->high_y;
	cub3d->fov = 60;

	// Initialize map
	map_list_t *current = stc;
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

    // Cleanup
    mlx_delete_image(cub3d->win, cub3d->img);
    mlx_terminate(cub3d->win);
    free(cub3d);

    return ;
}
