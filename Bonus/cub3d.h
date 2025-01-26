/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:25:42 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/26 22:15:23 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../GET_NEXT_LINE_42/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft_42/libft.h"
# include "../track_memory/memory_tracker.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"
# define PLAYER_SIZE 2
# define BUFFER 10

# define MAP_SIZE 100
# define CELL_SIZE 64
# define PLAYER_COLOR 0x0000FF00
# define WALL_COLOR 0x00FF0000
# define FLOOR_COLOR 0x00FFFFFF
# define SPECIAL_COLOR 0x0077CCFF
# define OUT_OF_BOUNDS_COLOR 0x00444444
# define SPEED 10.f
# define ROTATION_SPEED 0.05f
# define WIDTH 1024
# define HEIGHT 512
# define PI 3.1415926535
# define P1 PI / 2
# define P2 3 * PI / 2
# define DR 0.001022653859

typedef struct map_s	map_t;
typedef struct cordwal
{
	float				x;
	float				y;
	float				distance;
}						cordwal_t;

typedef struct ray_s
{
	//--------- horizontal -----------
	int r;          // Ray counter
	int mx, my, mp; // Map grid coordinates and position
	int dof;        // Depth of field
	float rx, ry;   // Ray position
	float ra;       // Ray angle
	float xo, yo;   // X and Y offsets
	float				aTan;

	//--------- vertitcal -----------
	float				vtan;
	float				distH;
	float				xH;
	float				yH;
	float				distV;
	float				dist;
	float				xh_was_adoor;
	float				yh_was_adoor;
	float				xv_was_adoor;
	float				yv_was_adoor;
	float				x_was_adoor;
	float				y_was_adoor;
	float				xV;
	float				yV;
	int					is_hori;
	int					is_door_h;
	int					is_door_v;
	int					is_door_close_h;
	int					is_door_close_v;
	int					is_door_close;
	int					dist_door;
	int					is_door;

}						ray_t;
// typedef struct texture_s
// {
//     float dist_project_plane;
//     float corrected_distance;
//     float wall_strip_height;
//     int wall_top;
//     int wall_bottom;
//     float texture_offset;

// }texture_t;
typedef struct cub3d_s
{
	float x;     // Player's x-coordinate
	float y;     // Player's y-coordinate
	float xdx;   // Player's direction vector x-component
	float ydy;   // Player's direction vector y-component
	float angle; // Player's current angle
	int					wall[3][1000];

	char **map;   // 2D map (walls and empty spaces)
	int map_x;    // Number of columns in the map
	int map_y;    // Number of rows in the map
	int map_unit; // Size of each square in the map (e.g., 64)
	float				pa;
	int					fov;
	int ray_dof_max; // Field of view (e.g., 60 degrees)
	int num_rays;    // Number of rays to cast (e.g., 60)
	ray_t				*ray;
	mlx_t *win;       // MiniLibX window
	mlx_image_t *img; // MiniLibX image to draw on
	mlx_image_t			**animation_frames;
	map_t				*info;

	//================
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
	uint8_t				a;

}						cub3d_t;

typedef struct map_list_s
{
	char				*map;
	int					length;
	int					ws;
	int					width_x;
	int					high_y;
	struct map_list_s	*next;
	struct map_list_s	*prev;
}						map_list_t;

typedef struct color_s
{
	bool				lock;
	int					r;
	int					g;
	int					b;

}						color_t;

typedef struct map_s
{
	map_list_t			*map_data;
	bool				map_str;
	bool				map_new_line;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	mlx_texture_t		*no_png;
	mlx_texture_t		*so_png;
	mlx_texture_t		*we_png;
	mlx_texture_t		*ea_png;
	mlx_texture_t		*door_png;

	mlx_texture_t		*wall_texture;
	mlx_texture_t		**Kickpng;
	double				last_time;
	int					i;

	float				dist_project_plane;
	float				corrected_distance;
	float				wall_strip_height;
	int					wall_top;
	int					wall_bottom;
	float				texture_offset;
	float				fov;

	char				*f;
	char				*c;

	color_t				*f_color;
	color_t				*c_color;
	tracker_t			**free_head;
}						map_t;

//-----------
//-----------texture

void					draw_wall(cub3d_t *cub, ray_t *ray, int ray_index,
							double s_agl);
int						loading_image(map_t *mp);

//-----------wall
void					main2(map_list_t *stc, map_t *color);
void					fill_maps(map_t *stc);
map_t					*parsing_first(int ac, char **av);
double					dist(float ax, float ay, float bx, float by);
int						init_ray(cub3d_t *cub);
int						draw_moraba3(int x, int y, int color, cub3d_t *cub);
int						draw_rays(cub3d_t *cub);
double					normalize_angle(double angle);
void					draw_ray(cub3d_t *cub, ray_t *rays);
void					handle_vertical_ray(cub3d_t *cub, double start_angle,
							ray_t *rays);
void					handle_horizontal_ray(cub3d_t *cub, double start_angle,
							ray_t *rays);

// ------------ animation -------------------- //
int						update_kick_animation(cub3d_t *cub3d);
void					init_kick_animation(cub3d_t *cub3d);
cub3d_t					*open_close_door(cub3d_t *cub, int k);
void					cleanup_animation_frames(cub3d_t *cub3d, int i);
// ------------ parsine -------------------- //

bool					is_char_here(const char *line, const char *chars);
void					trim_end(char *str);
void					remove_newline(char *line);
int						print_error(char *str);
void					close_file(int file);
int						parse_texture_line(map_t *stc, char **tokens);
int						door_check(map_list_t *hd);
int						process_map_file(map_t *stc, char *filename,
							tracker_t **free_head);
//============
void					free_at_exit(map_t *hd);
map_t					*init_map_structure(tracker_t **free_hd);
int						parse_line(map_t *stc, char *line);
void					close_file(int file);
int						check_zero(map_list_t *tmp, map_t *stc);
int						parse_line_maps(map_t *stc);
map_list_t				*add_map_list(map_list_t *head, char *map, map_t *stc);
int						word_count(char **str);
int						validate_texture_path(char *path, char *name);
int						validate_file_extension(char *ext);
int						in_color_range(color_t *color_);
int						color_erorr(char *str);
void					free_split(char **split);
int						parse_color(char *line, color_t *color);
void					trim_end(char *str);
void					check_current_positions(map_list_t *tmp, int i,
							map_t *stc);
void					check_adjacent_positions(map_list_t *tmp, int i,
							map_t *stc);
int						player_check(map_list_t *hd, map_t *stc);
void					remove_newline(char *line);
int						print_error(char *str);
void					draw_line(mlx_image_t *img, int x0, int y0, int x1,
							int y1, int color);
char					**ft_split(const char *s, char c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strdup_v2(const char *s1, tracker_t **free_head);
char					*ft_strjoin_v2(char const *s1, char const *s2,
							tracker_t **free_head);
size_t					ft_strlen(const char *s);
int						parse_map(int file, map_t *stc);
// int draw_plyr(mlx_image_t *img, int x, int y, float angle);

void					free_all(cub3d_t *cub);
double					dist(float ax, float ay, float bx, float by);
int						init_ray(cub3d_t *cub);
void					draw_mini_map(cub3d_t *cub);
cub3d_t					*open_close_door(cub3d_t *cub, int k);
int						check_mov(int x, int y, cub3d_t *cub);
void					free_all(cub3d_t *cub);
void					init_player(cub3d_t *cub);
void					ft_hook_v3(cub3d_t *cub3d);
void					ft_hook_v2(cub3d_t *cub3d, float *x, float *y);
cub3d_t					*init_cub_v1(map_list_t *stc, map_t *color);
void	itirate_horizontal(ray_t *rays, cub3d_t *cub);
void	itirate_vertical(ray_t *rays, cub3d_t *cub);
#endif
