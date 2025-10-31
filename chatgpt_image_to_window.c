#include <mlx.h>
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	png;
	t_img	canvas;
}	t_data;

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	int	offset = y * img->line_length + x * (img->bpp / 8);
	return (*(unsigned int *)(img->addr + offset));
}

void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	int	offset = y * img->line_length + x * (img->bpp / 8);
	*(unsigned int *)(img->addr + offset) = color;
}

int	main(void)
{
	t_data	data;
	int		x, y;
	unsigned int	color;

	// 1. Initialize MLX and window
	data.mlx = mlx_init();
	if (!data.mlx)
		return (printf("mlx_init failed\n"), 1);

	data.win = mlx_new_window(data.mlx, 800, 600, "PNG Pixel by Pixel");
	if (!data.win)
		return (printf("mlx_new_window failed\n"), 1);

	// 2. Load PNG
	data.png.img = mlx_png_file_to_image(data.mlx, "image.png",
		&data.png.width, &data.png.height);
	if (!data.png.img)
		return (printf("Failed to load PNG\n"), 1);

	data.png.addr = mlx_get_data_addr(data.png.img,
		&data.png.bpp, &data.png.line_length, &data.png.endian);

	// 3. Create canvas image (destination)
	data.canvas.img = mlx_new_image(data.mlx, 800, 600);
	data.canvas.addr = mlx_get_data_addr(data.canvas.img,
		&data.canvas.bpp, &data.canvas.line_length, &data.canvas.endian);

	// 4. Copy pixels manually
	for (y = 0; y < data.png.height; y++)
	{
		for (x = 0; x < data.png.width; x++)
		{
			color = get_pixel_color(&data.png, x, y);
			put_pixel(&data.canvas, x, y, color);
		}
	}

	// 5. Display the canvas
	mlx_put_image_to_window(data.mlx, data.win, data.canvas.img, 0, 0);

	// 6. Keep window open
	mlx_loop(data.mlx);
}
