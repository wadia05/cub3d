#include "cub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aloo;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	aloo = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (aloo == NULL)
		return (NULL);
	ft_strlcpy(aloo, s1, ft_strlen(s1) + 1);
	ft_strlcat(aloo, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (aloo);
}
int	loading_image(map_t *mp)
{
	char	filename[20];
	int		i;
	char	*path;

	// Load regular textures
	mp->no_png = mlx_load_png(mp->no);
	if (!mp->no_png)
		return (1);
	mp->so_png = mlx_load_png(mp->so);
	if (!mp->so_png)
		return (1);
	mp->ea_png = mlx_load_png(mp->ea);
	if (!mp->ea_png)
		return (1);
	mp->we_png = mlx_load_png(mp->we);
	if (!mp->we_png)
		return (1);
	mp->door_png = mlx_load_png("door.png");
	if (!mp->door_png)
		return (1);
	// Allocate memory for kick animation textures array
	mp->Kickpng = malloc(sizeof(mlx_texture_t *) * 23);
	if (!mp->Kickpng)
		return (1);
	// Load all kick animation frames
	i = 0;
	while (i < 23)
	{
		// Create filename string for each frame (1.png to 23.png)
		filename[0] = (i + 1) / 10 + '0'; // Tens digit
		filename[1] = (i + 1) % 10 + '0'; // Ones digit
		filename[2] = '.';
		filename[3] = 'p';
		filename[4] = 'n';
		filename[5] = 'g';
		filename[6] = '\0';
		path = ft_strjoin("kick/", filename);
		// Load the image
		mp->Kickpng[i] = mlx_load_png(path);
		printf("%s\n", path);
		if (!mp->Kickpng[i])
		{
			// Clean up previously loaded frames if current frame fails
			while (--i >= 0)
				mlx_delete_texture(mp->Kickpng[i]);
			free(mp->Kickpng);
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}
mlx_texture_t	*get_texturte(cub3d_t *cub, ray_t *ray, double s_agl)
{
	if (ray->is_door == 1)
	{
		return (cub->info->door_png);
	}
	else if (!ray->is_hori)
	{
		if (s_agl > 0 && s_agl < PI)
		{
			return (cub->info->so_png);
		}
		else
		{
			return (cub->info->no_png);
		}
	}
	else
	{
		if (s_agl > PI / 2 && s_agl < 3 * PI / 2)
		{
			return (cub->info->we_png);
		}
		else
		{
			return (cub->info->ea_png);
		}
	}
	return (NULL);
}
void	Render_ceiling(cub3d_t *cub, int ray_index)
{
	map_t		*txtur;
	int			y;
	uint32_t	ceiling_color;

	txtur = NULL;
	txtur = cub->info;
	(void)ray_index;
	y = -1;
	while (++y < txtur->wall_top)
	{
		if (cub->info->c_color)
		{
			ceiling_color = (cub->info->c_color->r << 24) | (cub->info->c_color->g << 16) | (cub->info->c_color->b << 8) | 0xFF;
		}
		mlx_put_pixel(cub->img, ray_index, y, ceiling_color);
	}
}
void	Render_floor(cub3d_t *cub, int ray_index)
{
	map_t		*txtur;
	uint32_t	floor_color;
	int			y;

	(void)ray_index;
	txtur = NULL;
	txtur = cub->info;
	floor_color = 0;
	y = txtur->wall_bottom + 1;
	while (y < HEIGHT)
	{
		if (cub->info->f_color)
		{
			floor_color = (cub->info->f_color->r << 24) | (cub->info->f_color->g << 16) | (cub->info->f_color->b << 8) | 0xFF;
		}
		mlx_put_pixel(cub->img, ray_index, y, floor_color);
		y++;
	}
}
int	Calculate_texture_X_coordinate(cub3d_t *cub, ray_t *ray, double s_agl)
{
	map_t	*txtur;
	float	texture_x;
	int		tex_x;

	txtur = cub->info;
	texture_x = 0;
	if (!ray->is_hori)
	{
		texture_x = fmod(ray->rx, cub->map_unit) / cub->map_unit;
		// Flip horizontal texture coordinate for west and south walls
		if (s_agl > 0 && s_agl < PI)
		{ // South wall
			texture_x = 1.0 - texture_x;
		}
	}
	else
	{
		texture_x = fmod(ray->ry, cub->map_unit) / cub->map_unit;
		// Flip horizontal texture coordinate for west wall
		if (s_agl > PI / 2 && s_agl < 3 * PI / 2)
		{ // West wall
			texture_x = 1.0 - texture_x;
		}
	}
	tex_x = (int)(texture_x * txtur->wall_texture->width);
	return (tex_x);
}

void	wall_top_bottom(cub3d_t **cub, ray_t *ray, double s_agl)
{
	float	overflow;
	map_t	*txtur;

	txtur = (*cub)->info;
	txtur->fov = PI / 3;
	txtur->dist_project_plane = (WIDTH / 2) / tan(txtur->fov / 2);
	// Apply fisheye correction and calculate wall height
	txtur->corrected_distance = ray->dist * cos((*cub)->angle - s_agl);
	txtur->wall_strip_height = ((*cub)->map_unit / txtur->corrected_distance)
		* txtur->dist_project_plane;
	// Calculate wall strip's vertical start and end positions
	txtur->wall_top = (HEIGHT / 2) - (txtur->wall_strip_height / 2);
	txtur->wall_bottom = (HEIGHT / 2) + (txtur->wall_strip_height / 2);
	// Handle cases where wall is taller than screen height
	txtur->texture_offset = 0.0f;
	if (txtur->wall_strip_height > HEIGHT)
	{
		overflow = txtur->wall_strip_height - HEIGHT;
		txtur->texture_offset = (overflow / 2) / txtur->wall_strip_height;
	}
	// printf ("%f\n",  txtur->texture_offset);
	txtur->wall_top = fmax(0, txtur->wall_top);
	txtur->wall_bottom = fmin(txtur->wall_bottom, HEIGHT - 1);
	// Modified texture selection logic to include doors
	txtur->wall_texture = NULL;
	txtur->wall_texture = get_texturte(*cub, ray, s_agl);
	// return (cub);
}
uint32_t	get_color_px(cub3d_t *cub, int texY, int texX)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	float		shade_factor;
	uint32_t	color;
	map_t		*txtur;

	txtur = cub->info;
	r = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width + texX)
		* 4];
	g = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width + texX)
		* 4 + 1];
	b = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width + texX)
		* 4 + 2];
	a = txtur->wall_texture->pixels[(texY * txtur->wall_texture->width + texX)
		* 4 + 3];
	shade_factor = 1.0f - (txtur->corrected_distance / (cub->map_unit * 10.0f));
	shade_factor = fmaxf(0.1f, fminf(shade_factor, 1.0f));
	color = ((uint8_t)(r * shade_factor) << 24 | (uint8_t)(g
				* shade_factor) << 16 | (uint8_t)(b * shade_factor) << 8 | a);
	return (color);
}

void	Draw_textured_wall_strip(cub3d_t *cub, int ray_index, int texX)
{
	map_t	*txtur;
	float	screen_pos;
	float	texture_y;
	int		texY;

	txtur = cub->info;
	// (void)ray_index;
	// (void)tex_x;
	// (void)tex_y;
	for (int y = txtur->wall_top; y <= txtur->wall_bottom; y++)
	{
		screen_pos = (float)(y - txtur->wall_top) / (txtur->wall_bottom
				- txtur->wall_top);
		texture_y = txtur->texture_offset + (screen_pos * (1.0f - 2.0f
					* txtur->texture_offset));
		texY = (int)(texture_y * txtur->wall_texture->height);
		texY = fmax(0, fmin(texY, txtur->wall_texture->height - 1));
		mlx_put_pixel(cub->img, ray_index, y, get_color_px(cub, texY, texX));
	}
}

void	draw_wall(cub3d_t *cub, ray_t *ray, int ray_index, double s_agl)
{
	int	tex_x;

	// map_t *txtur = cub->info;
	wall_top_bottom(&cub, ray, s_agl);
	// Calculate texture x-coordinate
	tex_x = Calculate_texture_X_coordinate(cub, ray, s_agl);
	// Render ceiling
	Render_ceiling(cub, ray_index);
	// Draw textured wall strip
	Draw_textured_wall_strip(cub, ray_index, tex_x);
	// Render floor
	Render_floor(cub, ray_index);
}
