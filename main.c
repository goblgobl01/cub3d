/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/21 16:30:09 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define MOVE_SPEED 0.05
#define ROTATION 0.1

void move(void *param)
{
	t_data *data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int) data->position_y][(int) (data->position_x + data->dir_x * MOVE_SPEED)] == '0')
			data->position_x += data->dir_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y + data->dir_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y += data->dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int) data->position_y][(int) (data->position_x - data->dir_x * MOVE_SPEED)] == '0')
			data->position_x -= data->dir_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y - data->dir_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y -= data->dir_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int) data->position_y][(int) (data->position_x + data->plane_x * MOVE_SPEED)] == '0')
			data->position_x += data->plane_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y + data->plane_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y += data->plane_y * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int) data->position_y][(int) (data->position_x - data->plane_x * MOVE_SPEED)] == '0')
			data->position_x -= data->plane_x * MOVE_SPEED;
		if (data->map[(int) (data->position_y - data->plane_y * MOVE_SPEED)][(int) data->position_x] == '0')
			data->position_y -= data->plane_y * MOVE_SPEED;
	}
	// if (keydata.key == MLX_KEY_LEFT)
	// {
	// 	double oldDirX = data->dir_x;
	// 	data->dir_x = data->dir_x * cos(-ROTATION) - data->dir_y * sin(-ROTATION);
	// 	data->dir_y = oldDirX * sin(-ROTATION) + data->dir_y * cos(-ROTATION);
	// 	double oldPlaneX = data->plane_x;
	// 	data->plane_x = data->plane_x * cos(-ROTATION) - data->plane_y * sin(-ROTATION);
	// 	data->plane_y = oldPlaneX * sin(-ROTATION) + data->plane_y * cos(-ROTATION);
	// }
	// if (keydata.key == MLX_KEY_RIGHT)
	// {
	// 	double oldDirX = data->dir_x;
	// 	data->dir_x = data->dir_x * cos(ROTATION) - data->dir_y * sin(ROTATION);
	// 	data->dir_y = oldDirX * sin(ROTATION) + data->dir_y * cos(ROTATION);
	// 	double oldPlaneX = data->plane_x;
	// 	data->plane_x = data->plane_x * cos(ROTATION) - data->plane_y * sin(ROTATION);
	// 	data->plane_y = oldPlaneX * sin(ROTATION) + data->plane_y * cos(ROTATION);
	// }
	// debug_view(data);
	raycasting(data);
} 

int main(int ac, char **av)
{
	t_data	*data;
	FILE *fptr = fopen("log.txt", "a");

	if (ac != 2 || !checking_arguments(av[1]))
	{
		write(2, "Error\n invalid_arguments\n", 25);
		exit(1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		write(2, "Error\n couldn't allocate memmory\n", 33);
		exit(1);
	}
	data->fptr = fptr;
	intializing_all_variables(&data);
	reading_map_file(av[1], data);
	// line added by youssef:
	mlx_loop_hook(data->mlx, &move, data);
		// line added by youssef:
	// mlx_loop_hook(data->mlx, raycasting_wrapper, data);
	mlx_loop(data->mlx);
	// lines added by youssef:
	mlx_delete_texture(data->NO_Texture);
	mlx_delete_texture(data->SO_Texture);
	mlx_delete_texture(data->WE_Texture);
	mlx_delete_texture(data->EA_Texture);
}
