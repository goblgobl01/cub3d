#include "MLX/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SIDE 1300

void print_wall(mlx_image_t *img, int x, float distance)
{
	int nearness = SIDE - (distance / 6 * SIDE);
	int i = 0;

	while (i < (SIDE - nearness) / 2)
	{
		mlx_put_pixel(img, x, i, 0x0000FFFF); // Blue (RGBA)
		i++;
	}
	while (i < nearness + (SIDE - nearness) / 2)
	{
		mlx_put_pixel(img, x, i, 0x90E0FF); // Wall color (RGBA)
		i++;
	}
	while (i < SIDE)
	{
		mlx_put_pixel(img, x, i, 0x00FF00FF); // Green (RGBA)
		i++;
	}
}

int main(void)
{
	mlx_t *mlx;
	mlx_image_t *img;

	mlx = mlx_init(SIDE, SIDE, "Cub3D", false);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	img = mlx_new_image(mlx, SIDE, SIDE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		puts(mlx_strerror(mlx_errno));
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}

	int i = 0;
	float distance = 0;
	while (i < SIDE)
	{
		print_wall(img, i, distance);
		distance += 0.005;
		i++;
	}

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
