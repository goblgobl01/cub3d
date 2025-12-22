/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/22 17:01:38 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void leaks(void) {
// 	system("leaks cub3D");
// }

int	main(int ac, char **av)
{
	t_data	*data;

	// atexit(leaks);
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
	intializing_all_variables(&data);
	reading_map_file(av[1], data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, &move, data);
	mlx_loop(data->mlx);
	free_everything(data);
}
