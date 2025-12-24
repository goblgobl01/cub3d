/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:32:36 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/24 09:39:50 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	error_function(char *str, t_data *data)
{
	int	length;

	length = ft_strlen(str);
	write(2, str, length);
	free_everything_stage_1(data);
	exit(1);
}

void	free_everything_stage_2(t_data *data)
{
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
}

void	free_everything_stage_1(t_data *data)
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
	if (data->map_fd != -1)
		close(data->map_fd);
	free_everything_stage_2(data);
	if (data)
		free(data);
}

int	inside_charset(char c)
{
	int		i;
	char	*charset;

	charset = " \f\n\r\t\v";
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
