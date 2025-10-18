/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:41:04 by codespace         #+#    #+#             */
/*   Updated: 2025/10/18 17:48:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void error_function(char *str, t_data *data)
{
	int	length;

	length = ft_strlen(str);
	write(2, str, length);
	free_everything(data);
	exit(1);
}

void	free_everything(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->big_line)
		free (data->big_line);
	if (data->NO)
		free (data->NO);
	if (data->SO)
		free (data->SO);
	if (data->WE)
		free (data->WE);
	if (data->EA)
		free (data->EA);
	if (data->F)
		free (data->F);
	if (data->C)
		free (data->C);
	if (data)
		free(data);
}

int	inside_charset(char c)
{
	int	i;
	char *charset = " \f\n\r\t\v";

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (inside_charset(str[i]))
		{
			i++;
			continue ;
		}
		while (str[i] && !inside_charset(str[i]))
			i++;
		count++;
	}
	return (count);
}


int	checking_arguments(char *str)
{
	int		length;
	char	*string;
	int		i;

	length = ft_strlen(str);
	string = "buc.";
	length--;
	i = 0;
	while (i < 4)
	{
		if (str[length] == *string)
		{
			string++;
			length--;
		}
		else
			return (0);
		i++;
	}
	if (str[length] == '/')
		return (0);
	return (1);
}

void	intializing_all_variables(t_data **data)
{
	(*data)->map = NULL;
	(*data)->big_line = NULL;
	(*data)->NO = NULL;
	(*data)->SO = NULL;
	(*data)->WE = NULL;
	(*data)->EA = NULL;
	(*data)->F = NULL;
	(*data)->C = NULL;
	(*data)->player_direction = 0;
	(*data)->starting_position_x = 0;
	(*data)->starting_position_y = 0;
	(*data)->map_height = 0;
	(*data)->map_width = 0;
	(*data)->parameters_count = 0;
}
void check_texture(char *str, t_data *data)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_function("Error\n invalid texture\n", data);
	else
		close (fd);
}

int args_length(char **args)
{
	int	i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}

void check_rgb_values(char *str, t_data *data)
{
	char	**args;
	int		length;
	int		i;
	int		value;

	args = ft_charset_split(str, ",");
	length = args_length(args);
	if (length != 3)
		error_function("Error\n invalid rgb: should have only 3 values\n", data);
	i = 0;
	while(args[i])
	{
		value = ft_atoi(args[i]);
		if (value > 255 || value < 0)
			error_function("Error\n invalid rgb: values should be between 0 and 255\n", data);
		i++;
	}
}

void	check_path_and_rgb_values(t_data *data)
{
	check_texture(data->NO, data);
	check_texture(data->SO, data);
	check_texture(data->WE, data);
	check_texture(data->EA, data);
	check_rgb_values(data->F, data);
	check_rgb_values(data->C, data);
}

int check_empty_lines(char *ptr)
{
	int i;

	i = 0;
	while(ptr[i])
	{
		if (!inside_charset(ptr[i]))
			return (0);
		i++;
	}
	return (1);
}

void check_first_letters_and_asign(char *ptr, t_data *data)
{
	char	**args;
	int		length;

	args = ft_charset_split(ptr, " \f\n\r\t\v");
	length = ft_strlen(args[0]);
	if (args[0][0] == 'F' && length == 1 && data->F == NULL)
		data->F = ft_strdup(args[1]);
	else if (args[0][0] == 'C' && length == 1 && data->C == NULL)
		data->C = ft_strdup(args[1]);
	else if ((args[0][0] == 'S' && args[0][1] == 'O') && length == 2 && data->SO == NULL)
		data->SO = ft_strdup(args[1]);
	else if ((args[0][0] == 'N' && args[0][1] == 'O') && length == 2 && data->NO == NULL)
		data->NO = ft_strdup(args[1]);
	else if ((args[0][0] == 'W' && args[0][1] == 'E') && length == 2 && data->WE == NULL)
		data->WE = ft_strdup(args[1]);
	else if ((args[0][0] == 'E' && args[0][1] == 'A') && length == 2 && data->EA == NULL)
		data->EA = ft_strdup(args[1]);
	else
		error_function("Error\n invalid map input 2\n", data);
	data->parameters_count++;
	(free(args[0]), free(args[1]), free(args));
}

void intializing_textures_path(int fd, t_data *data)
{
	char	*ptr;
	int		word_count;

	(void) data;
	while ((ptr = get_next_line(fd)) && data->parameters_count != 6)
	{
		if (check_empty_lines(ptr))
		{
			free(ptr);
			continue ;
		}
		else
		{
			word_count = count_words(ptr);
			if (word_count != 2)
				error_function("Error\n invalid map input 1\n", data);
			check_first_letters_and_asign(ptr, data);
		}
		free(ptr);
	}
}



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

void parse_the_map(int fd,t_data *data)
{
	char *ptr;

	while((ptr = get_next_line(fd)))
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
		ptr = get_next_line(fd);
		if (!ptr)
			break ;
		// if (check_empty_lines(ptr)) //ojdajl;adk
		// {
		// 	free(ptr);
		// 	error_function("Error\n map shouldn't contain empty lines\n", data);
		// }
	}
	close (fd);
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

void checking_map_walls(t_data *data)
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
				 || data->map[y][x] == 'E' || data->map[y][x] == 'W'
				 || data->map[y][x] == '0')
			{
				if (data->map[y][x + 1] != '0' && data->map[y][x + 1] != '1')
					error_function("Error\n map error\n", data);
				if (data->map[y][x - 1] != '0' && data->map[y][x - 1] != '1')
					error_function("Error\n map error\n", data);
				if (data->map[y + 1][x] != '0' && data->map[y + 1][x] != '1')
					error_function("Error\n map error\n", data);
				if (data->map[y - 1][x] != '0' && data->map[y - 1][x] != '1')
					error_function("Error\n map error\n", data);
			}
			x++;
		}
		y++;
	}
}

void	map_checking(t_data *data)
{
	data->map = ft_split(data->big_line, '\n');
	if (!(data->map))
		error_function("Error\n map_checking\n", data);
	if (data->player_count != 1)
		error_function("Error\n must have only one player\n", data);
	locating_player_position(data);
	checking_map_walls(data);
}

void reading_map_file(char *str, t_data *data)
{
	// char	*ptr;
	int		fd;
	// int		length;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\n", 6), free(data), exit(1), (void)0);
	intializing_textures_path(fd, data);
	check_path_and_rgb_values(data);
	parse_the_map(fd, data);
	// map_checking(data);
}