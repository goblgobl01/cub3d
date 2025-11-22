#include "header.h"

void	wall_height(t_data	*data)
{
	data->line_height = (int)(screenHeight / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + screenHeight / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + screenHeight / 2;
	if (data->draw_end > screenHeight)
		data->draw_end = (screenHeight - 1);
}

void	ceiling(t_data *data, int x)
{
	int y;

	y = 0;
	while (y < data->draw_start)
	{
		mlx_put_pixel(data->img, x, y, 0x87CEEBFF);
		y++;
	}
}
void	wall(t_data *data, int x)
{
	int y;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		mlx_put_pixel(data->img, x, y, 0x808080FF);
		y++;
	}
}
void	floor_r(t_data *data, int x)
{
	int y;

	y = data->draw_end;
	while (y < screenHeight)
	{
		mlx_put_pixel(data->img, x, y, 0x228B22FF);
		y++;
	}
	// printf("x --> %d\n", x);
}