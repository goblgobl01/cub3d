/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:54:33 by codespace         #+#    #+#             */
/*   Updated: 2025/12/22 10:10:50 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

uint32_t	get_pixel(t_data *data, int x, int y)
{
	mlx_texture_t	*texture;
	uint8_t			*pixel;
	uint8_t			r, g, b, a;
	uint32_t		color;

	texture = data->Texture;
	pixel = texture->pixels + (y * texture->width + x) * 4;
	a = pixel[0];
	r = pixel[1];
	g = pixel[2];
	b = pixel[3];
	color = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}

void calculating_tex_x(t_data *data)
{
	float wall_x;
	
	if (data->side == 0)
	{
		if (data->ray_dir_x > 0)
			data->Texture = data->WE_Texture;
		else
			data->Texture = data->EA_Texture;
		wall_x = data->position_y + data->perp_wall_dist * data->ray_dir_y;
	}
	else
	{
		if (data->ray_dir_y > 0)
			data->Texture = data->SO_Texture;
		else
			data->Texture = data->NO_Texture;
		wall_x = data->position_x + data->perp_wall_dist * data->ray_dir_x;
	}
	wall_x -= floor(wall_x);
	data->tex_x = (int)(wall_x * ((float)data->Texture->width));
	if (data->side == 0 && data->ray_dir_x < 0)
		data->tex_x = ((float)data->Texture->width) - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y > 0)
		data->tex_x = ((float)data->Texture->width) - data->tex_x - 1;
}

void print_wall(t_data *data, int x)
{
	int		nearness, wall_end, i, color, tex_y;
	float	step, tex_pos;

    nearness = (int)(screenHeight / data->perp_wall_dist);
    wall_end = (screenHeight - nearness) / 2 + nearness;
    if (wall_end > screenHeight)
		wall_end = screenHeight;
    i = 0;
    while (i < (screenHeight - nearness) / 2)
        mlx_put_pixel(data->img, x, i++, 0x0000FFFF);
	calculating_tex_x(data);
	step = ((float)data->Texture->height)/ nearness;
	tex_pos = (fmax(0.0, (float)(screenHeight - nearness) / 2) + (nearness - screenHeight) / 2) * step;
    while (i < wall_end)
	{
		tex_y = (int)fmax(0.0, tex_pos);
		tex_pos += step;
		color = get_pixel(data, data->tex_x, tex_y);
        mlx_put_pixel(data->img, x, i++, color);
	}
    while (i < screenHeight)
        mlx_put_pixel(data->img, x, i++, 0x00FF00FF);
}

void initialize_parameters(int x, t_data *data)
{
	data->camera_x = 2 * x / (double) screenWidth - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)data->position_x;
	data->map_y = (int)data->position_y;
	if (data->ray_dir_x == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = fabs(1/data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = fabs(1/data->ray_dir_y);
	data->hit = 0;
	if (data->ray_dir_x < 0)
	{
		data->step_x= -1;
		data->side_dist_x = (data->position_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x= 1;
		data->side_dist_x = (data->map_x + 1 - data->position_x) * data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y= -1;
		data->side_dist_y = (data->position_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1 - data->position_y) * data->delta_dist_y;
	}
}

void raycasting(t_data *data)
{
	int	x;
	x = 0;
	while(x < screenWidth)
	{
		initialize_parameters(x, data);
		while (data->hit == 0)
		{
			if (data->side_dist_x < data->side_dist_y)
			{
				data->side_dist_x += data->delta_dist_x;
				data->map_x += data->step_x;
				data->side = 0;
			}
			else
			{
				data->side_dist_y += data->delta_dist_y;
				data->map_y += data->step_y;
				data->side = 1;
			}
			if (data->map[data->map_y][data->map_x] != '0')
			{
				data->hit = 1;
			}
		}
		if(data->side == 0)
			data->perp_wall_dist = (data->side_dist_x - data->delta_dist_x);
		else
			data->perp_wall_dist = (data->side_dist_y - data->delta_dist_y);
		print_wall(data, x);
		x++;
	}
}
