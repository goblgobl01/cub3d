/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:54:33 by codespace         #+#    #+#             */
/*   Updated: 2025/12/24 10:21:23 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calculate_first_dist_and_assign_step(t_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->pos_x - data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1 - data->pos_x) * data->delta_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->pos_y - data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1 - data->pos_y) * data->delta_y;
	}
}

void	initialize_parameters(int x, t_data *data)
{
	data->camera_x = 2 * x / (double) screenWidth - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)data->pos_x;
	data->map_y = (int)data->pos_y;
	if (data->ray_dir_x == 0)
		data->delta_x = 1e30;
	else
		data->delta_x = fabs(1 / data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->delta_y = 1e30;
	else
		data->delta_y = fabs(1 / data->ray_dir_y);
	data->hit = 0;
	calculate_first_dist_and_assign_step(data);
}

void	perform_dda_loop(t_data *data)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->map[data->map_y][data->map_x] != '0')
		{
			data->hit = 1;
		}
	}
}

void	raycasting(t_data *data)
{
	int	x;

	x = 0;
	while (x < screenWidth)
	{
		initialize_parameters(x, data);
		perform_dda_loop(data);
		if (data->side == 0)
			data->perp_wall_dist = (data->side_dist_x - data->delta_x);
		else
			data->perp_wall_dist = (data->side_dist_y - data->delta_y);
		print_wall(data, x);
		x++;
	}
}
