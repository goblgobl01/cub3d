/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGBtoINT.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:17:29 by ytlidi            #+#    #+#             */
/*   Updated: 2025/12/22 19:16:44 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*getred(char *str)
{
	char	*r;
	int		i;

	r = malloc(4);
	i = 0;
	while (str[i] != ',')
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*getgreen(char *str)
{
	char	*g;
	int		i;
	int		j;

	g = malloc(4);
	i = 0;
	while (str[i] != ',')
		i++;
	i++;
	j = 0;
	while (str[i] != ',')
	{
		g[j] = str[i];
		i++;
		j++;
	}
	g[j] = '\0';
	return (g);
}

char	*getblue(char *str)
{
	char	*b;
	int		i;
	int		j;

	b = malloc(4);
	i = 0;
	while (str[i] != ',')
		i++;
	i++;
	while (str[i] != ',')
		i++;
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		b[j] = str[i];
		i++;
		j++;
	}
	b[j] = '\0';
	return (b);
}

int	rgb2int(char *str)
{
	char	*red;
	char	*green;
	char	*blue;
	int		color;

	red = getred(str);
	green = getgreen(str);
	blue = getblue(str);
	color = ft_atoi(red);
	color <<= 8;
	color += ft_atoi(green);
	color <<= 8;
	color += ft_atoi(blue);
	color <<= 8;
	color += 0xFF;
	free(red);
	free(green);
	free(blue);
	return (color);
}
