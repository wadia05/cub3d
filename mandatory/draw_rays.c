/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/228 16:15:21 by abenchel          #+#    #+#             */
/*   Updated: 2024/12/10 19:04:14 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_moraba3(int x, int y, int color, cub3d_t *cub)
{
    int i = 0;
    int j;

    // Reduce the size of each cube by 1 pixel to create a gap
    
    while (i < cub->map_unit)
    {
        j = 0;
        while(j < cub->map_unit)
        {
            mlx_put_pixel(cub->img, x+i, y+j, color);
            j++;
        }
        i++;
    }
    return 0;
}
