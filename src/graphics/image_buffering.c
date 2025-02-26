#include "cub3d.h"

void	put_floor_ceiling(t_img *background, int *c_color, int *f_color, void *mlx)
{
	int	x;
	int	y;

	(void)c_color;
	(void)f_color;
	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			if (y < 300)
				mlx_pixel_put(mlx, background, x, y, 196);
			else
				mlx_pixel_put(mlx, background, x, y, 200);
			x++;
		}
		y++;
	}
}

void	default_buffer(int	*c_color, int *f_color)
{
	t_img	default_img;
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	default_img.img = mlx_new_image(mlx, 800, 600);
	put_floor_ceiling(&default_img, c_color, f_color, mlx);
	win = mlx_new_window(mlx, 800, 600, "cub3d");
	mlx_put_image_to_window(mlx, win, default_img.img, 0, 0);
}
