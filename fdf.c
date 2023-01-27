#include "fdf.h"


void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


int	keys(int key, t_data *mlx)
{
	if (key == ESC)
	{
		exit(0);
		return (0);
	}
	return (0);
}

int	ft_exit(void)
{
	exit(1);
	return (0);
}

int    main(void)
{
    t_data    mlx;

    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 1080, "Hello world!");
    mlx.img = mlx_new_image(mlx.mlx, 1080, 1080);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
                                &mlx.endian);


	int y_start = 400;
	int y_end = 800;
	int x_start = 200;
	int x_end = 500;

	while(y_start < y_end)
	{
		x_start = 200;
		while(x_start < x_end)
		{
			my_mlx_pixel_put(&mlx.mlx, x_start, y_start, 0x00FFFFFF);
			x_start++;
		}
    	y_start++;    
	}


    mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_hook(mlx.mlx_win, 17, 2, ft_exit, (void *)0);
	mlx_key_hook(mlx.mlx_win, keys, (void *)&mlx);
    mlx_loop(mlx.mlx);

	
}




// cc main.c -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm && ./a.out
