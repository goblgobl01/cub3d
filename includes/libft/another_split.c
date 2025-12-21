/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:52:46 by codespace         #+#    #+#             */
/*   Updated: 2025/10/21 19:04:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int inside_charset(char c, char *charset)
{
	int i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int count_words(char *str, char *charset)
{
	int i = 0;
	int count = 1; // Start with 1 to count the segment before the first delimiter

	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (inside_charset(str[i], charset))
			count++;
		i++;
	}
	return (count);
}

static void allocate_duplicate(char *str, char *charset, char **strs)
{
	int i = 0, start = 0, k = 0;

	while (str[i])
	{
		if (inside_charset(str[i], charset))
		{
			strs[k] = malloc((i - start) + 1);
			if (!strs[k])
				return ;
			ft_memcpy(strs[k], str + start, i - start);
			strs[k][i - start] = '\0';
			k++;
			i++;
			start = i;
		}
		else
			i++;
	}
	// Add the last element (can be empty if string ends with a delimiter)
	strs[k] = malloc((i - start) + 1);
	ft_memcpy(strs[k], str + start, i - start);
	strs[k][i - start] = '\0';
	k++;
	strs[k] = NULL;
}

char **another_split(char *str, char *charset)
{
	char **strs;
	int count;

	if (!str || !charset)
		return (NULL);
	count = count_words(str, charset);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	allocate_duplicate(str, charset, strs);
	return (strs);
}

