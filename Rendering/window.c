#include "../MLX/include/MLX42/MLX42.h"
#define SIDE 1300
typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

void put_pixel(t_img *img, int x, int y, int color)
{
    int offset;

    offset = y * img->line_length + x * (img->bits_per_pixel / 8);
    *(unsigned int *)(img->addr + offset) = color;
}

void print_wall(t_img *img, int x, float distance)
{
	int nearness = SIDE / (distance + 1);
	int i = 0;
	while (i < (SIDE - nearness) / 2)
	{
		put_pixel(img, x, i, 0x0000FF);
		i++;
	}
	while (i < nearness + (SIDE - nearness) / 2)
	{
		put_pixel(img, x, i, 9502975);
		i++;
	}
	while (i < SIDE)
	{
		put_pixel(img, x, i, 0x00FF00);
		i++;
	}
}
int main()
{
	void *mlx;
	void *win;
	t_img img;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1300, 1300, "Cub3d");
	img.img = mlx_new_image(mlx, 1300, 1300);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
                                      &img.line_length, &img.endian);
	int i = 0;
	float distance = 0;
	while(i < 1300)
	{
		print_wall(&img, i, distance);
		distance += 0.05;
		i++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}