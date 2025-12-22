#ifndef HEADER_H
#define HEADER_H

#include "includes/libft/libft.h"
#include <fcntl.h>
#include "stdio.h"
#include <math.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include "MLX42/include/MLX42/MLX42.h"
#define screenWidth 1280
#define screenHeight 720
#define MOVE_SPEED 0.05
#define ROTATION 0.05

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
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	unsigned int	map_height;
	int				draw_start;
	int				draw_end;
	int				line_height;
	mlx_image_t		*img;
	mlx_t			*mlx;
	mlx_texture_t	*NO_Texture;
	mlx_texture_t	*SO_Texture;
	mlx_texture_t	*WE_Texture;
	mlx_texture_t	*EA_Texture;
	mlx_texture_t	*Texture;
	int				tex_x;
	int				tex_y;
}t_data;

void		free_everything(t_data *data);
int			checking_arguments(char *str);
void		intializing_all_variables(t_data **data);
void		error_function(char *str, t_data *data);
void		reading_map_file(char *str, t_data *data);
void		intializing_textures_path(int fd, t_data *data);
int			check_empty_lines(char *ptr);
void		raycasting(t_data *data);
void		intializing_raycasting_variables(t_data *data);
void		wall_height(t_data *data);
void		ceiling(t_data *data, int x);
void		wall(t_data *data, int x);
void		floor_r(t_data *data, int x);
void		debug_view(t_data *data);
void		initialize_parameters(int x, t_data *data);
void		move(void *param);
void		print_wall(t_data *data, int x);
void		calculating_tex_x(t_data *data);
uint32_t	get_pixel(t_data *data, int x, int y);
void		leaks(t_data *data);

#endif