/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:41:23 by codespace         #+#    #+#             */
/*   Updated: 2025/11/20 22:42:44 by mmaarafi         ###   ########.fr       */
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
	(*data)->parameters_count = 0;
	(*data)->player_count = 0;
	// lines added by youssef:
	(*data)->NO_Texture = mlx_load_png("Drawing.png");
	(*data)->SO_Texture = mlx_load_png("Drawing.png");
	(*data)->WE_Texture = mlx_load_png("Drawing.png");
	(*data)->EA_Texture = mlx_load_png("Drawing.png");
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
	int		flag;
 
	flag = 0;
	args = another_split(str, ",");
	i = 0;
	// while(args[i])
	// {
	// 	printf("%s\n",args[i]);
	// 	i++;
	// }
	// printf("this is str: %s\n", str);
	length = args_length(args);
	// printf("length : %d\n", length);
	if (length != 3)
		error_function("Error\n invalid rgb: should have only 3 values\n", data);
	i = 0;
	while(args[i])
	{
		value = ft_atoi_improved(args[i], &flag);
		// printf("value : %d\n", value);
		if ((value > 255 || value < 0))
			error_function("Error\n invalid rgb: values should be between 0 and 255->1\n", data);
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

void check_first_letters_and_assign(char *ptr, t_data *data)
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

void	intializing_textures_path(int fd, t_data *data)
{
	char	*ptr;
	int		word_count;

	(void) data;
	while ((ptr = get_next_line(fd)))
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
			check_first_letters_and_assign(ptr, data);
		}
		free(ptr);
		if (data->parameters_count == 6)
			break ;
	}
	check_path_and_rgb_values(data);
}
