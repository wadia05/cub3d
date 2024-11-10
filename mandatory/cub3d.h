/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:25:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/11/10 10:22:11 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../GET_NEXT_LINE_42/get_next_line.h"
#include "../track_memory/memory_tracker.h"
# include "../libft_42/libft.h"
# include <math.h>
# include <stdio.h>
#include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <string.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

# define WIDTH 1024
# define HEIGHT 512
# define PI 3.1415926535
# define P1 PI/2
# define P2 3*PI/2
# define DR 0.0174533

typedef struct map_list_s
{
    char *map;
    int length;
    int ws;
    struct map_list_s *next;
    struct map_list_s *prev;
} map_list_t;

typedef struct color_s
{
    int r;
    int g;
    int b;

} color_t;

typedef struct map_s
{
    map_list_t *map_data;
    char *no;
    char *so;
    char *we;
    char *ea;


    char *f;
    char *c;

    color_t *f_color;
    color_t *c_color;

} map_t;
void trim_end(char *str);
void check_adjacent_positions(map_list_t *tmp, int i);
void check_current_position(map_list_t *tmp, int i);
int player_check(map_list_t *hd);
void remove_newline(char *line);
int print_error(char *str);
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
char	**ft_split(const char *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int parse_map(int file, map_t *stc);
// int draw_plyr(mlx_image_t *img, int x, int y, float angle);

#endif
