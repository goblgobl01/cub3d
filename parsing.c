/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:41:04 by codespace         #+#    #+#             */
/*   Updated: 2025/12/24 10:17:26 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	locating_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->starting_x = x;
				data->starting_y = y;
			}
			x++;
		}
		y++;
	}
}

void	check_errors(unsigned int x, unsigned int y, t_data *data)
{
	if (x == 0 || y == 0)
		error_function("Error\n map error\n", data);
	if (y == (data->map_height - 1))
		error_function("Error\n map error0\n", data);
	if (data->map[y][x + 1] != '0' && data->map[y][x + 1] != '1'
		&& data->map[y][x + 1] != 'N' && data->map[y][x + 1] != 'S'
		&& data->map[y][x + 1] != 'E' && data->map[y][x + 1] != 'W')
		error_function("Error\n map error1\n", data);
	if (data->map[y][x - 1] != '0' && data->map[y][x - 1] != '1'
		&& data->map[y][x - 1] != 'N' && data->map[y][x - 1] != 'S'
		&& data->map[y][x - 1] != 'E' && data->map[y][x - 1] != 'W')
		error_function("Error\n map error2\n", data);
	if ((x > ft_strlen(data->map[y + 1]))
		|| (data->map[y + 1][x] != '0' && data->map[y + 1][x] != '1'
		&& data->map[y + 1][x] != 'N' && data->map[y + 1][x] != 'S'
		&& data->map[y + 1][x] != 'E'
		&& data->map[y + 1][x] != 'W'))
		error_function("Error\n map error3\n", data);
	if ((x > ft_strlen(data->map[y - 1]))
		|| (data->map[y - 1][x] != '0' && data->map[y - 1][x] != '1'
		&& data->map[y - 1][x] != 'N' && data->map[y - 1][x] != 'S'
		&& data->map[y - 1][x] != 'E'
		&& data->map[y - 1][x] != 'W'))
		error_function("Error\n map error4\n", data);
}

void	checking_map(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (data->map[y])
	{
		if (*data->map[y] == 0)
			error_function("Error\n this map error\n", data);
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W'
				|| data->map[y][x] == '0')
				check_errors(x, y, data);
			x++;
		}
		y++;
	}
}

void	map_checking(t_data *data)
{
	data->map = another_split(data->big_line, "\n");
	if (!(data->map))
		error_function("Error\n map_checking\n", data);
	if (data->player_count != 1)
		error_function("Error\n must have only one player\n", data);
	data->map_height = calculating_map_height(data->map);
	locating_player_position(data);
	checking_map(data);
}

void	reading_map_file(char *str, t_data *data)
{
	data->map_fd = open(str, O_RDONLY);
	if (data->map_fd < 0)
		error_function("Error\n couldn't open map file\n", data);
	intializing_textures_path(data->map_fd, data);
	parse_the_map(data);
	map_checking(data);
	intializing_raycasting_variables(data);
	raycasting(data);
}
