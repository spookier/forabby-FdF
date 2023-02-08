#include "fdf.h"
#include "mlx_int.h"

#define SIZE_X 10
#define SIZE_Y 10
#define ZOOM 10

typedef float			t_v2f __attribute__((vector_size (8)));
typedef unsigned int	t_v2u __attribute__((vector_size (8)));
typedef int				t_v2i __attribute__((vector_size (8)));

void    my_mlx_pixel_put(t_data *data, t_v2i pos, int color)
{
    char    *dst;

	if (pos[0] >= data->line_length / 4 || pos[0] < 0 || pos[1] >= ((t_img *)data->img)->height || pos[1] < 0)
		return ;
    dst = data->addr + (pos[1] * data->line_length + pos[0] * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	put_line(t_data *data, t_v2i p1, t_v2i p2, int color)
{
	t_v2f	diff;
	t_v2f	start;
	int		count;

	diff = (t_v2f){p2[0], p2[1]} - (t_v2f){p1[0], p1[1]};
	if (fabsf(diff[0]) > fabsf(diff [1]))
	{
		count = fabsf(diff[0]);
		diff = diff / fabsf(diff[0]);
	}
	else
	{
		count = fabsf(diff[1]);
		diff = diff / fabsf(diff[1]);
	}
	start = (t_v2f){p1[0], p1[1]};
	while (count)
	{
		my_mlx_pixel_put(data, (t_v2i){start[0], start[1]}, color);
		start = start + diff;
		count--;
	}
}

void	put_rect(t_data *data, t_v2i start, t_v2i dim, int color)
{
	t_v2i	pos;

	pos[1] = 0;
	while(pos[1] < dim[1])
	{
		pos[0] = 0;
		while(pos[0] < dim[0])
		{
			my_mlx_pixel_put(data, start + pos, 0x00FFFFFF);
    		pos[0]++;
		}
    	pos[1]++;
	}
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


t_v2i	v2ir(float rot, float dist)
{
	return ((t_v2i){sinf(rot) * dist, cosf(rot) * dist});
}

int	get_map(int map[SIZE_X][SIZE_Y], t_v2i size, t_v2i pos)
{
	if (pos[0] < 0 || pos[1] < 0 || pos[0] >= size[0] || pos[1] >= size[1])
		return (0);
	return (map[pos[0]][pos[1]]);
}

int    main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		map[SIZE_X][SIZE_Y];

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1080, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, (t_v2i){5, 5}, 0x00FF0000);
	int y_start = 400;
	int y_end = 800;
	int x_start = 200;
	int x_end = 500;


	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
		{
			map[x][y] = rand() % 10;
		}

	while (1)
	{
	t_v2i	pos;
	t_v2i	point;
	int		val[3];

	put_rect(&img, (t_v2i){0, 0}, (t_v2i){1080, 1080}, 0x000000);
	for (pos[1] = 0; pos[1] < SIZE_Y; pos[1]++)
		for (pos[0] = 0; pos[0] < SIZE_X; pos[0]++)
		{
			val[0] = get_map(map, (t_v2i){SIZE_X, SIZE_Y}, pos);
			val[1] = get_map(map, (t_v2i){SIZE_X, SIZE_Y}, pos + (t_v2i){1, 0});
			val[2] = get_map(map, (t_v2i){SIZE_X, SIZE_Y}, pos + (t_v2i){0, 1});
			point = (t_v2i){ZOOM * 5, 540} + (t_v2i){pos[0] * 5 + pos[1] * 5, pos[0] * -3 + pos[1] * 3} * ZOOM;
			put_line(&img, point + ((t_v2i){-5, 0} + (t_v2i){0, -val[0]}) * ZOOM, point + ((t_v2i){0, -3} + (t_v2i){0, -val[1]}) * ZOOM, 0xAE80AE);
			put_line(&img, point + ((t_v2i){-5, 0} + (t_v2i){0, -val[0]}) * ZOOM, point + ((t_v2i){0, 3} + (t_v2i){0, -val[2]}) * ZOOM, 0xAE80AE);
		}

	// t_v2i 	start = (t_v2i){x_start, y_start};

	// //put_rect(&img, start, (t_v2i){200, 300}, 0xAE80AE);

	// float	rot = 200.0f;
	// put_line(&img, start, start + v2ir(rot, 200), 0xAE80AE);
	//  rot += 0.125f;
	// put_line(&img, start, start + v2ir(rot, 200), 0xAE80AE);
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
		{
			map[x][y] = map[(x + 1) % SIZE_X][y];
		}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	usleep(100000);
	}
	mlx_loop(mlx);
}




// cc main.c -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm && ./a.out
