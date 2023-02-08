#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "mlx_linux/mlx.h"

# define ESC		0xFF1B

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif
