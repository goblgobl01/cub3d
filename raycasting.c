/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:54:33 by codespace         #+#    #+#             */
/*   Updated: 2025/12/04 16:45:31 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// function added by youssef:
// void print_wall(t_data *data, int x)
// {
//     //if (data->perp_wall_dist <= 0.01)
//     //    data->perp_wall_dist = 0.01;

//     int nearness = (int)(screenHeight / data->perp_wall_dist);

//     int start = (screenHeight - nearness) / 2;
//     int end   = start + nearness;

//     //if (start < 0) start = 0;
//     if (end > screenHeight) end = screenHeight;

//     int i = 0;

//     while (i < start)
//         mlx_put_pixel(data->img, x, i++, 0x0000FFFF);

//     while (i < end)
//         mlx_put_pixel(data->img, x, i++, 0x90E0FF);

//     while (i < screenHeight)
//         mlx_put_pixel(data->img, x, i++, 0x00FF00FF);
// }

void initialize_parameters(int x, t_data *data)
{
	data->camera_x = 2 * x / (double) screenWidth - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = data->starting_position_x;
	data->map_y = data->starting_position_y;
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
	// line deleted by youssef:
	// intializing_raycasting_variables(data);
	x = 0;
	// printf("sc");
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
				data->hit = 1;
		}
		if(data->side == 0)
			data->perp_wall_dist = (data->side_dist_x - data->delta_dist_x);
		else
			data->perp_wall_dist = (data->side_dist_y - data->delta_dist_y);
		// wall_height(data);
		// ceiling(data, x);
		// wall(data, x);
		// floor_r(data, x);
		// line added by youssef:
		// print_wall(data, x);
		printf("rays distant: %f\n", data->perp_wall_dist);
		x++;
	}
	// printf("end x ->%d s w  %d\n", x, screenWidth);
	mlx_image_to_window(data->mlx, data->img, 0 , 0);
}
