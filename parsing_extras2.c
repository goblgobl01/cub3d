/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:37:17 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/24 15:13:39 by mmaarafi         ###   ########.fr       */
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
	(*data)->NO = NULL;
	(*data)->SO = NULL;
	(*data)->WE = NULL;
	(*data)->EA = NULL;
	(*data)->F = NULL;
	(*data)->C = NULL;
	(*data)->player_direction = 0;
	(*data)->starting_x = 0;
	(*data)->starting_y = 0;
	(*data)->map_height = 0;
	(*data)->parameters_count = 0;
	(*data)->player_count = 0;
	(*data)->map_fd = -1;
	(*data)->EA_Texture = NULL;
	(*data)->WE_Texture = NULL;
	(*data)->SO_Texture = NULL;
	(*data)->NO_Texture = NULL;
	(*data)->img = NULL;
	(*data)->mlx = NULL;
}

void	check_texture(char *str, t_data *data)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_function("Error\n invalid texture\n", data);
	else
		close (fd);
}

int	args_length(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_args(int length, char **args)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
