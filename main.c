#include "mlx_linux/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_coordinates {

	int x;
	int x1;
	int y;
	int y1;	

}	t_coordinates;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_line(t_data *data, t_coordinates *pos, int color)
{
	int i = 0;
	while(i < pos->x1)
	{
		my_mlx_pixel_put(data, pos->x, pos->y, color);
		pos->x = pos->x + 1;
		i++;
	}


}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1080, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000)

	t_coordinates pos_line = {100, 800, 1080/2, 1080/2};
	draw_line(&img, &pos_line, 0xFFFFFF);



	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}


// cc main.c -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm && ./a.out