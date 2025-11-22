/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_extras.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 06:19:24 by codespace         #+#    #+#             */
/*   Updated: 2025/11/21 19:08:36 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	intializing_raycasting_variables(t_data *data)
{
	if (data->map[data->starting_position_y][data->starting_position_x] == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->map[data->starting_position_y][data->starting_position_x] == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->map[data->starting_position_y][data->starting_position_x] == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->map[data->starting_position_y][data->starting_position_x] == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
	data->position_x = data->starting_position_x + 0.5;
	data->position_y = data->starting_position_y + 0.5;
	data->map[data->starting_position_y][data->starting_position_x] = '0';
	data->mlx = mlx_init(screenWidth, screenHeight, "CUB3D", 0);
    data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
}