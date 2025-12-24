/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:24:56 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/24 15:03:22 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	apply_move(t_data *data, double move_x, double move_y)
{
	if (data->map[(int)data->pos_y][(int)(data->pos_x + move_x)] == '0')
		data->pos_x += move_x;
	if (data->map[(int)(data->pos_y + move_y)][(int)data->pos_x] == '0')
		data->pos_y += move_y;
}

void	apply_rotation(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}

void	move(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		apply_move(data, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		apply_move(data, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		apply_move(data, data->plane_x * MOVE_SPEED,
			data->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		apply_move(data, -data->plane_x * MOVE_SPEED,
			-data->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		apply_rotation(data, -ROTATION);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		apply_rotation(data, ROTATION);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	raycasting(data);
}
