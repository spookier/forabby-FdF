MLX_FLAGS= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm
COMPILER=cc


ex:
	$(COMPILER) fdf.c $(MLX_FLAGS) && ./a.out 

clean:
	rm -rf a.out