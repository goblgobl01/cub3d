/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:24:56 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/22 10:25:47 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void move(void *param)
{
	t_data *data = (t_data *) param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int) data->position_y][(int) ((data->position_x + data->dir_x * MOVE_SPEED))] == '0')
			data->position_x += data->dir_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y + data->dir_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y += data->dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int) data->position_y][(int) ((data->position_x - data->dir_x * MOVE_SPEED))] == '0')
			data->position_x -= data->dir_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y - data->dir_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y -= data->dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int) data->position_y][(int) ((data->position_x + data->plane_x * MOVE_SPEED))] == '0')
			data->position_x += data->plane_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y + data->plane_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y += data->plane_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int) data->position_y][(int) ((data->position_x - data->plane_x * MOVE_SPEED))] == '0')
			data->position_x -= data->plane_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y - data->plane_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y -= data->plane_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROTATION) - data->dir_y * sin(-ROTATION);
		data->dir_y = oldDirX * sin(-ROTATION) + data->dir_y * cos(-ROTATION);
		double oldPlaneX = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROTATION) - data->plane_y * sin(-ROTATION);
		data->plane_y = oldPlaneX * sin(-ROTATION) + data->plane_y * cos(-ROTATION);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = data->dir_x;
		data->dir_x = data->dir_x * cos(ROTATION) - data->dir_y * sin(ROTATION);
		data->dir_y = oldDirX * sin(ROTATION) + data->dir_y * cos(ROTATION);
		double oldPlaneX = data->plane_x;
		data->plane_x = data->plane_x * cos(ROTATION) - data->plane_y * sin(ROTATION);
		data->plane_y = oldPlaneX * sin(ROTATION) + data->plane_y * cos(ROTATION);
	}
	raycasting(data);
} 