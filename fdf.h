#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "stdlib.h"
#include "mlx_linux/mlx.h"
#include "math.h"

#include "stdio.h"


typedef struct s_coordinates {

	int x;
	int x1;
	int y;
	int y1;	

}	t_coordinates;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;




#endif
