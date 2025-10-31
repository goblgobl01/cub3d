#include <MLX42/MLX42.h>
#include <stdio.h>
#include <stdint.h>

uint32_t	get_pixel(mlx_t *mlx, const char *file, int x, int y)
{
	mlx_texture_t	*texture;
	uint8_t			*pixel;
	uint8_t			r, g, b, a;
	uint32_t		color;

	texture = mlx_load_png(file);

	pixel = texture->pixels + (y * texture->width + x) * 4;
	r = pixel[0];
	g = pixel[1];
	b = pixel[2];
	a = pixel[3];
	color = (a << 24) | (r << 16) | (g << 8) | b;

	mlx_delete_texture(texture);
	return (color);
}

int	main(void)
{
	mlx_t		*mlx;
	uint32_t	color;
	int			x = 13;
	int			y = 69;

	mlx = mlx_init(1, 1, "Get Pixel", false);
	color = get_pixel(mlx, "image.png", x, y);
	printf("Pixel (%d,%d): color = 0x%08X\n", x, y, color);
	mlx_terminate(mlx);
}
