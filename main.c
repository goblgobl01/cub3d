/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/18 16:48:57 by codespace        ###   ########.fr       */
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
	printf("+++++++++++++++++++++++\n");
	printf("SO: |%s|\n", data->SO);
	printf("NO: |%s|\n", data->NO);
	printf("WE: |%s|\n", data->WE);
	printf("EA: |%s|\n", data->EA);
	printf("F: |%s|\n", data->F);
	printf("C: |%s|\n", data->C);
	printf("map:\n");
	printf("%s\n", data->big_line);
	printf("+++++++++++++++++++++++\n");
}

// ===== first elements ====
// Except for the map content, each type of element can be separated by one or more empty lines.
// Except for the map content which always has to be the last, each type of element can be set in any order in the file.
// Except for the map, each type of information from an element can be separated by one or more spaces.
// each element must begin with its type identifier (composed by one or two characters),
// followed by its specific information in a strict order

// ===== the map=======
// The map must be composed of only 6 possible characters: 0 for an empty space,
// 1 for a wall, and N,S,E or W for the player’s start position and spawning
// orientation.
// The map must be closed/surrounded by walls, if not the program must return
// an error.
// The map must be parsed as it looks in the file. Spaces are a valid part of the
// map and are up to you to handle. You must be able to parse any kind of map,
// as long as it respects the rules of the map

// handle duplicate

// and handle 6 correct parameter then a duplicate.

// rgb not over 255 and only 3 parameters

// for the map i only need to check the zero on the map neet to be surrounded either by walls or by zero and the player also.