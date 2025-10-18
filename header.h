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
	char		*F;
	char		*C;
	char		player_direction;
	int			parameters_count;
	int			player_count;
	int			starting_position_x;
	int			starting_position_y;
	int			map_height;
	int			map_width;
}t_data;

void	free_everything(t_data *data);
int		checking_arguments(char *str);
void	intializing_all_variables(t_data **data);
void	error_function(char *str, t_data *data);
void	reading_map_file(char *str, t_data *data);
void	intializing_textures_path(int fd, t_data *data);
int		check_empty_lines(char *ptr);


#endif