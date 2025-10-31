#include "MLX/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	mlx_t		*mlx;
	mlx_texture_t	*texture;
	uint8_t		*pixel;
	uint32_t	color;
	uint8_t		r, g, b, a;
	int			x = 42;
	int			y = 42;

	// 1. Initialize MLX42 (window is not needed just for texture loading)
	mlx = mlx_init(1, 1, "Get Pixel", false);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX42\n");
		return (EXIT_FAILURE);
	}

	// 2. Load the PNG texture
	texture = mlx_load_png("Drawing.png");
	if (!texture)
	{
		fprintf(stderr, "Failed to load image.png\n");
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}

	// 3. Check bounds
	if (x < 0 || y < 0 || x >= (int)texture->width || y >= (int)texture->height)
	{
		fprintf(stderr, "Coordinates out of bounds\n");
		mlx_delete_texture(texture);
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}

	// 4. Get pointer to pixel (RGBA: 4 bytes per pixel)
	pixel = texture->pixels + (y * texture->width + x) * 4;

	// 5. Extract color components
	r = pixel[0];
	g = pixel[1];
	b = pixel[2];
	a = pixel[3];

	color = (a << 24) | (r << 16) | (g << 8) | b;

	printf("Pixel (%d, %d): color = 0x%08X | R=%d G=%d B=%d A=%d\n",
		x, y, color, r, g, b, a);

	// 6. Clean up
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
