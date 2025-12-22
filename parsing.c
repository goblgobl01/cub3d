/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:41:04 by codespace         #+#    #+#             */
/*   Updated: 2025/12/22 15:34:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*strcatt(char *dest, const char *src)
{
	int	length_dest;
	int	i;

	i = 0;
	length_dest = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[length_dest + i] = src[i];
		i++;
	}
	dest[length_dest + i] = '\0';
	return (dest);
}

char	*strjoinn(char *stash, char *buffer)
{
	int		length;
	char	*str;

	if (!stash && !buffer)
		return (NULL);
	if (!stash)
		return (ft_strdup(buffer));
	if (!buffer)
		return (ft_strdup(stash));
	length = ft_strlen(stash) + ft_strlen(buffer);
	str = malloc(length + 1);
	if (str == NULL)
		return (free(stash), NULL);
	str[0] = '\0';
	strcatt(str, stash);
	strcatt(str, buffer);
	free(stash);
	return (str);
}

int	is_valid_character(char c, t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = " \f\n\r\t\v01NSEW\n";
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->player_count++;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	characters_checking(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (!str)
		error_function("Error\n there is no map\n", data);
	while (str[i])
	{
		if (!is_valid_character(str[i], data))
			return (0);
		i++;
	}
	return (1);
}

void parse_the_map(t_data *data)
{
	char *ptr;

	while((ptr = get_next_line(data->map_fd)))
	{
		if (check_empty_lines(ptr))
			free(ptr);
		else
			break ;
	}
	while (ptr)
	{
		data->big_line = strjoinn(data->big_line, ptr);
		free(ptr);
		ptr = get_next_line(data->map_fd);
		if (!ptr)
			break ;
	}
	if (!characters_checking(data->big_line, data))
		error_function("Error\n invalid_characters\n", data);
}

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
				data->starting_position_x = x;
				data->starting_position_y = y;
			}
			x++;
		}
		y++;
	}
}

void checking_map(t_data *data)
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
			{
				if (x == 0 || y == 0)
					error_function("Error\n map error\n", data);
				if (y == (data->map_height - 1))
					error_function("Error\n map error0\n",data);
				if (data->map[y][x + 1] != '0' && data->map[y][x + 1] != '1'
					&& data->map[y][x + 1] != 'N' && data->map[y][x + 1] != 'S'
					&& data->map[y][x + 1] != 'E' && data->map[y][x + 1] != 'W')
					error_function("Error\n map error1\n", data);
				if (data->map[y][x - 1] != '0' && data->map[y][x - 1] != '1'
					&& data->map[y][x - 1] != 'N' && data->map[y][x - 1] != 'S'
					&& data->map[y][x - 1] != 'E' && data->map[y][x - 1] != 'W')
					error_function("Error\n map error2\n", data);
				if ((x > ft_strlen(data->map[y + 1])) || (data->map[y + 1][x] != '0' && data->map[y + 1][x] != '1'
					&& data->map[y + 1][x] != 'N' && data->map[y + 1][x] != 'S'
					&& data->map[y + 1][x] != 'E' && data->map[y + 1][x] != 'W'))
					error_function("Error\n map error3\n", data);
				if ((x > ft_strlen(data->map[y - 1])) || (data->map[y - 1][x] != '0' && data->map[y - 1][x] != '1'
					&& data->map[y - 1][x] != 'N' && data->map[y - 1][x] != 'S'
					&& data->map[y - 1][x] != 'E' && data->map[y - 1][x] != 'W'))
					error_function("Error\n map error4\n", data);
			}
			x++;
		}
		y++;
	}
}

int	calculating_map_height(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	return (i);
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

void reading_map_file(char *str, t_data *data)
{
	data->map_fd = open(str, O_RDONLY);
	if (data->map_fd < 0)
		error_function("Error\n couldn't open map file\n", data);
	intializing_textures_path(data->map_fd, data);
	parse_the_map(data);
	map_checking(data);
	// intializing_raycasting_variables(data);
	// raycasting(data);
}