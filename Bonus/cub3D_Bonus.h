/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_Bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:25:42 by wait-bab          #+#    #+#             */
/*   Updated: 2025/01/29 23:55:45 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define DR 0.001022653859

typedef struct map_s	t_map;

typedef struct ray_s
{
	int					r;
	int					mx;
	int					my;
	int					mp;
	int					dof;
	float				rx;
	float				ry;
	float				ra;
	float				xo;
	float				yo;
	float				atan;
	float				vtan;
	float				disth;
	float				xh;
	float				yh;
	float				distv;
	float				dist;
	float				xh_was_adoor;
	float				yh_was_adoor;
	float				xv_was_adoor;
	float				yv_was_adoor;
	float				x_was_adoor;
	float				y_was_adoor;
	float				xv;
	float				yv;
	int					is_hori;
	int					is_door_h;
	int					is_door_v;
	int					is_door_close_h;
	int					is_door_close_v;
	int					is_door_close;
	int					dist_door;
	int					is_door;

}						t_ray;

typedef struct cub3d_s
{
	float				x;
	float				y;
	float				xdx;
	float				ydy;
	float				angle;
	int					wall[3][1000];
	int					add_x;
	int					add_y;
	char				**map;
	int					map_x;
	int					map_y;
	int					map_unit;
	float				pa;
	int					fov;
	int					ray_dof_max;
	int					num_rays;
	t_ray				*ray;
	mlx_t				*win;
	mlx_image_t			*img;
	mlx_image_t			**animation_frames;
	t_map				*info;

	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
	uint8_t				a;

	int32_t				mouse_x;
	int32_t				mouse_y;

}						t_cub3d;

typedef struct map_list_s
{
	char				*map;
	int					length;
	int					ws;
	int					width_x;
	int					high_y;
	struct map_list_s	*next;
	struct map_list_s	*prev;
}						t_map_list;

typedef struct color_s
{
	bool				lock;
	int					r;
	int					g;
	int					b;

}						t_color;

typedef struct map_s
{
	t_map_list			*map_data;
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
	mlx_texture_t		**kickpng;
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

	t_color				*f_color;
	t_color				*c_color;
	t_tracker			**free_head;
}						t_map;

void					draw_wall(t_cub3d *cub, t_ray *ray, int ray_index,
							double s_agl);
int						loading_image(t_map *mp);
mlx_texture_t			*get_texturte(t_cub3d *cub, t_ray *ray, double s_agl);
void					render_ceiling(t_cub3d *cub, int ray_index);
void					render_floor(t_cub3d *cub, int ray_index);

void					main2(t_map_list *stc, t_map *color);
void					fill_maps(t_map *stc);
t_map					*parsing_first(int ac, char **av);
double					dist(float ax, float ay, float bx, float by);
int						init_ray(t_cub3d *cub);
int						draw_moraba3(int x, int y, int color, t_cub3d *cub);
int						draw_rays(t_cub3d *cub);
double					normalize_angle(double angle);
void					draw_ray(t_cub3d *cub, t_ray *rays);
void					handle_vertical_ray(t_cub3d *cub, double start_angle,
							t_ray *rays);
void					handle_horizontal_ray(t_cub3d *cub, double start_angle,
							t_ray *rays);

int						update_kick_animation(t_cub3d *cub3d);
void					init_kick_animation(t_cub3d *cub3d);
t_cub3d					*open_close_door(t_cub3d *cub, int k);
void					cleanup_animation_frames(t_cub3d *cub3d, int i);

bool					is_char_here(const char *line, const char *chars);
void					trim_end(char *str);
void					remove_newline(char *line);
int						print_error(char *str);
void					close_file(int file);
int						parse_texture_line(t_map *stc, char **tokens);
int						door_check(t_map_list *hd);
int						process_map_file(t_map *stc, char *filename,
							t_tracker **free_head);

void					free_at_exit(t_map *hd);
t_map					*init_map_structure(t_tracker **free_hd);
int						parse_line(t_map *stc, char *line);
void					close_file(int file);
int						check_zero(t_map_list *tmp, t_map *stc);
int						parse_line_maps(t_map *stc);
t_map_list				*add_map_list(t_map_list *head, char *map, t_map *stc);
int						word_count(char **str);
int						validate_texture_path(char *path, char *name);
int						validate_file_extension(char *ext);
int						in_color_range(t_color *color_);
int						color_erorr(char *str);
void					free_split(char **split);
int						parse_color(char *line, t_color *color);
void					trim_end(char *str);
void					check_current_positions(t_map_list *tmp, int i,
							t_map *stc);
void					check_adjacent_positions(t_map_list *tmp, int i,
							t_map *stc);
int						player_check(t_map_list *hd, t_map *stc);
void					remove_newline(char *line);
int						print_error(char *str);
char					**ft_split(const char *s, char c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strdup_v2(const char *s1, t_tracker **free_head);
char					*ft_strjoin_v2(char const *s1, char const *s2,
							t_tracker **free_head);
size_t					ft_strlen(const char *s);

void					free_all(t_cub3d *cub);
double					dist(float ax, float ay, float bx, float by);
int						init_ray(t_cub3d *cub);
void					draw_mini_map(t_cub3d *cub);
t_cub3d					*open_close_door(t_cub3d *cub, int k);
int						check_mov(int x, int y, t_cub3d *cub);
void					free_all(t_cub3d *cub);
void					init_player(t_cub3d *cub);
void					ft_hook_v3(t_cub3d *cub3d);
void					ft_hook_v2(t_cub3d *cub3d, float *x, float *y);
t_cub3d					*init_cub_v1(t_map_list *stc, t_map *color);
void					itirate_horizontal(t_ray *rays, t_cub3d *cub);
void					itirate_vertical(t_ray *rays, t_cub3d *cub);
void					ft_hook(void *param);
void					ft_hook_mouse(void *param);
void					cleanup_all(t_cub3d *cub3d);
void					handle_movement(t_cub3d *cub3d);
void					handle_animation(t_cub3d *cub3d);
#endif