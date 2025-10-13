/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:06:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/10/13 11:53:15 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main()
{
	int fd = open("file", O_RDONLY);
	
	printf("fd :%d\n", fd);
	char *str = NULL;
	str = get_next_line(fd);
	printf("line :%s", str);
	str = get_next_line(fd);

	printf("line :%s", str);
	str = get_next_line(fd);
	printf("line :%s", str);
}