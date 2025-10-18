/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charset_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:11:23 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/17 17:55:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inside_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (inside_charset(str[i], charset))
		{
			i++;
			continue ;
		}
		while (str[i] && !inside_charset(str[i], charset))
			i++;
		count++;
	}
	return (count);
}

static void	allocate_duplicate(char *str, char *charset, int count, char **strs)
{
	int	i;
	int	j;
	int	k;
	int	l;

	l = 0;
	k = 0;
	i = 0;
	while (k < count)
	{
		if (inside_charset(str[i], charset))
		{
			i++;
			continue ;
		}
		j = i;
		while (str[i] && !inside_charset(str[i], charset))
			i++;
		strs[k] = malloc((i - j) + 1);
		while (j < i)
			strs[k][l++] = str[j++];
		strs[k++][l] = 0;
		l = 0;
	}
	strs[k] = NULL;
}

char	**ft_charset_split(char *str, char *charset)
{
	char	**strs;
	int		count;

	count = count_words(str, charset);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	allocate_duplicate(str, charset, count, strs);
	return (strs);
}
