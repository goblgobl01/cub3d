#ifndef HEADER_H
#define HEADER_H

#include "includes/libft/libft.h"
#include <fcntl.h>
#include "stdio.h"
#include <math.h>
#include <limits.h>
#include <float.h>
#define screenWidth 640
#define screenHeight 480

typedef struct s_struct
{
	char			**map;
	char			*big_line;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*F;
	char			*C;
	char			player_direction;
	int				parameters_count;
	int				player_count;
	int				starting_position_x;
	int				starting_position_y;
	double			position_x;
	double			position_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	//length of ray from current position to next x or y-side
	double			side_dist_x;
	double			side_dist_y;
	//length of ray from one x or y-side to next x or y-side
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	//what direction to step in x or y-direction (either +1 or -1)
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	unsigned int	map_height;
}t_data;

void	free_everything(t_data *data);
int		checking_arguments(char *str);
void	intializing_all_variables(t_data **data);
void	error_function(char *str, t_data *data);
void	reading_map_file(char *str, t_data *data);
void	intializing_textures_path(int fd, t_data *data);
int		check_empty_lines(char *ptr);
void	raycasting(t_data *data);
void	intializing_raycasting_variables(t_data *data);


#endif