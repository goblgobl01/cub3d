/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/13 15:06:29 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	(*data)->player_direction = NULL;
	(*data)->starting_position_x = 0;
	(*data)->starting_position_y = 0;
	(*data)->map_height = 0;
	(*data)->map_width = 0;
}

void reading_map_file(char *str, t_data *data)
{
	char	*ptr;
	int		fd;
	int		length;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\n", 6), free(data), exit(1), (void)0);
	intializing_textures(fd);
}

int main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || !checking_arguments(av[1]))
	{
		write(2, "Error\n invalid_arguments", 25);
		exit(1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		write(2, "Error\n couldn't allocate memmory", 33);
		exit(1);
	}
	intializing_all_variables(&data);
	reading_map_file(av[1], &data);
}

// prerequisite:
// Except for the map content, each type of element can be separated by one or more empty lines.
// Except for the map content which always has to be the last, each type of element can be set in any order in the file.
// Except for the map, each type of information from an element can be separated by one or more spaces.
// each element must begin with its type identifier (composed by one or two characters), followed by its specific information in a strict order

