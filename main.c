#include "mlx_linux/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(void)
{
	void	*mlx;
	t_data	img;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 800, 600);


	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
}
// cc main.c -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm && ./a.out