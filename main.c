/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/21 16:31:33 by ytlidi           ###   ########.fr       */
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
	(*data)->s_img = NULL;
	(*data)->g_img = NULL;
	(*data)->w_img = NULL;
	(*data)->c_img = NULL;
	(*data)->e_img = NULL;
	(*data)->mlx = NULL;
	(*data)->exit = 0;
	(*data)->height = 0;
	(*data)->player = 0;
	(*data)->collectible = 0;
	(*data)->ffc = 0;
	(*data)->ffe = 0;
	(*data)->move_count = 0;
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
}