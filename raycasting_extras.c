/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_extras.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 06:19:24 by codespace         #+#    #+#             */
/*   Updated: 2025/12/24 10:32:19 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initializing_raycasting_variables_stage1(t_data *data)
{
	if (data->map[data->starting_y][data->starting_x] == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->map[data->starting_y][data->starting_x] == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->map[data->starting_y][data->starting_x] == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->map[data->starting_y][data->starting_x] == 'W')
		return (data->dir_x = -1, data->dir_y = 0,
			data->plane_x = 0, data->plane_y = -0.66, (void) 0);
}

void	intializing_raycasting_variables(t_data *data)
{
	initializing_raycasting_variables_stage1(data);
	data->pos_x = data->starting_x + 0.5;
	data->pos_y = data->starting_y + 0.5;
	data->map[data->starting_y][data->starting_x] = '0';
	data->mlx = mlx_init(screenWidth, screenHeight, "CUB3D", 0);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->NO_Texture = mlx_load_png(data->NO);
	data->SO_Texture = mlx_load_png(data->SO);
	data->WE_Texture = mlx_load_png(data->WE);
	data->EA_Texture = mlx_load_png(data->EA);
}
