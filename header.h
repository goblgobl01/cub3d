#ifndef HEADER_H
#define HEADER_H

#include "includes/libft/libft.h"
#include <fcntl.h>
#include "stdio.h"

typedef struct s_struct
{
	char		**map;
	char		*big_line;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		player_direction;
	int			parameters_count;
	int			starting_position_x;
	int			starting_position_y;
	int			map_height;
	int			map_width;
}t_data;

#endif