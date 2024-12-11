/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:25:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/12/11 12:54:59 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../MLX42/include/MLX42/MLX42.h"
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

# define WIDTH 1024
# define HEIGHT 512
# define PI 3.1415926535
# define P1 PI / 2
# define P2 3 * PI / 2
# define DR 0.0174533

typedef struct map_list_s
{
	char				*map;
	int					length;
	int					ws;
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

	char				*f;
	char				*c;

	color_t				*f_color;
	color_t				*c_color;
	tracker_t			*free_head;

}						map_t;

void					free_at_exit(map_t *hd);
map_t	*init_map_structure(tracker_t *free_hd);
int	parse_line(map_t *stc, char *line);
void	close_file(int file);
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
char					*ft_strdup_v2(const char *s1, tracker_t *free_head);
char					*ft_strjoin_v2(char const *s1, char const *s2,
							tracker_t *free_head);
size_t					ft_strlen(const char *s);
int						parse_map(int file, map_t *stc);
// int draw_plyr(mlx_image_t *img, int x, int y, float angle);

#endif
