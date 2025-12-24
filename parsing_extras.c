/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:41:23 by codespace         #+#    #+#             */
/*   Updated: 2025/12/24 09:37:15 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_rgb_values(char *str, t_data *data)
{
	char	**args;
	int		length;
	int		i;
	int		value;
	int		flag;

	flag = 0;
	args = another_split(str, ",");
	i = 0;
	length = args_length(args);
	if (length != 3)
		return (free_args(length, args), 
			error_function("Error\n only 3 values\n", data));
	i = 0;
	while (args[i])
	{
		value = ft_atoi_improved(args[i], &flag);
		if ((value > 255 || value < 0))
		{
			free_args(length, args);
			error_function("Error\n values should be between 0 and 255\n", data);
		}
		i++;
	}
	free_args(length, args);
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

int	check_empty_lines(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (!inside_charset(ptr[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_first_letters_and_assign(char *ptr, t_data *data)
{
	char	**args;

	args = ft_charset_split(ptr, " \f\n\r\t\v");
	if (args[0][0] == 'F' && ft_strlen(args[0]) == 1 && data->F == NULL)
		data->F = ft_strdup(args[1]);
	else if (args[0][0] == 'C' && ft_strlen(args[0]) == 1 && data->C == NULL)
		data->C = ft_strdup(args[1]);
	else if ((args[0][0] == 'S' && args[0][1] == 'O')
				&& ft_strlen(args[0]) == 2 && data->SO == NULL)
		data->SO = ft_strdup(args[1]);
	else if ((args[0][0] == 'N' && args[0][1] == 'O')
				&& ft_strlen(args[0]) == 2 && data->NO == NULL)
		data->NO = ft_strdup(args[1]);
	else if ((args[0][0] == 'W' && args[0][1] == 'E')
				&& ft_strlen(args[0]) == 2 && data->WE == NULL)
		data->WE = ft_strdup(args[1]);
	else if ((args[0][0] == 'E' && args[0][1] == 'A')
				&& ft_strlen(args[0]) == 2 && data->EA == NULL)
		data->EA = ft_strdup(args[1]);
	else
		return (free_args(3, args), free(ptr),
			error_function("Error\n invalid map input 2\n", data));
	data->parameters_count++;
	free_args(3, args);
}

void	intializing_textures_path(int fd, t_data *data)
{
	char	*ptr;
	int		word_count;

	while (1)
	{
		ptr = get_next_line(fd);
		if (check_empty_lines(ptr))
		{
			free(ptr);
			continue ;
		}
		else
		{
			word_count = count_words(ptr);
			if (word_count != 2)
				return (free(ptr),
					error_function("Error\n invalid map input 1\n", data));
			check_first_letters_and_assign(ptr, data);
		}
		free(ptr);
		if (data->parameters_count == 6)
			break ;
	}
	check_path_and_rgb_values(data);
}
