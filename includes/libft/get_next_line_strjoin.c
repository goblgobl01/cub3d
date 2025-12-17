/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_strjoin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:59:01 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/13 11:04:12 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strjoin(char *stash, char *buffer)
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
	my_strcat(str, stash);
	my_strcat(str, buffer);
	free(stash);
	return (str);
}
