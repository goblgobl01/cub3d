/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/11/21 02:11:29 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int ac, char **av)
{
	t_data	*data;

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
	mlx_loop(data->mlx);
	// printf("+++++++++++++++++++++++\n");
	// printf("SO: |%s|\n", data->SO);
	// printf("NO: |%s|\n", data->NO);
	// printf("WE: |%s|\n", data->WE);
	// printf("EA: |%s|\n", data->EA);
	// printf("F: |%s|\n", data->F);
	// printf("C: |%s|\n", data->C);
	// printf("map:\n");
	// printf("%s\n", data->big_line);
	// printf("+++++++++++++++++++++++\n");
}
