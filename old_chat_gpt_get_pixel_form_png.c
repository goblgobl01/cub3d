#include <MLX42.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	int	offset;
	unsigned int	color;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0); // Out of bounds

	offset = y * img->line_length + x * (img->bpp / 8);
	color = *(unsigned int *)(img->addr + offset);
	return (color);
}

int	main(void)
{
	void	*mlx;
	t_img	png;
	unsigned int	color;
	int		r, g, b;

	// 1. Initialize MLX
	mlx = mlx_init();
	if (!mlx)
		return (printf("mlx_init failed\n"), 1);

	// 2. Load PNG image
	png.img = mlx_png_file_to_image(mlx, "Drawing.png", &png.width, &png.height);
	if (!png.img)
		return (printf("Failed to load image.png\n"), 1);

	// 3. Get raw pixel data
	png.addr = mlx_get_data_addr(png.img, &png.bpp, &png.line_length, &png.endian);

	// 4. Get color at (42, 42)
	color = get_pixel_color(&png, 42, 42);

	// 5. Extract RGB components
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	printf("Pixel (42,42): color = 0x%08X | R=%d G=%d B=%d\n", color, r, g, b);

	return (0);
}
