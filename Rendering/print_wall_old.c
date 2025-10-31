#include <mlx.h>
#define SIDE 1300
typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

void print_wall(t_img *img, int x, int distance)
{
	int nearness = SIDE - distance;
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