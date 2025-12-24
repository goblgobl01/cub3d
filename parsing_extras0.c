/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:24:38 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/12/24 09:39:45 by mmaarafi         ###   ########.fr       */
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

void	parse_the_map(t_data *data)
{
	char	*ptr;

	while (1)
	{
		ptr = get_next_line(data->map_fd);
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
