#ifndef FRACT_OL_H
# define FRACT_OL_H
# include <mlx.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# define HEIGHT 700 
# define WIDTH 700 
# define R 255 - (i * 3)
# define G 255 - (i * 15)
# define B 255 * fabs(sin((double)i * 4))

# ifdef __linux__
#  define ESC 65307
# else
#  define ESC 53
# endif

typedef struct s_img {
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_img	img;
}				t_vars;

typedef struct s_pos {
	double	pos_x;
	double	pos_y;
	int		height_adpt;
	int		width_adpt;
	double	zoom;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	delta_x;
	double	delta_y;
	double	mouse_x1;
	double	mouse_x2;
	double	mouse_y1;
	double	mouse_y2;
	int		iter_multiplier;
	int		iter_count;
	double	c_r;
	double	c_i;
	int		set;
}				t_pos;

typedef struct s_all {
	t_vars	*v;
	t_pos	*p;
}				t_all;

int		close_window(int keycode, t_vars *vars);
int		iter_mandelbrot(double x, double y, t_pos *pos);
int		iter_julia(double x, double y, t_pos *pos);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	get_image(t_pos *pos);
void	img_pxl_put(t_img *img, int x, int y, int color);
int		create_mandelbrot(t_pos *pos, t_vars *vars);
int		create_julia(t_pos *pos, t_vars *vars);
void	zoom_in(t_pos *pos);
void	zoom_out(t_pos *pos);
void	zoom_from_mouse_position(int x, int y, t_pos *pos);
void	window_adapt(t_pos *pos);
int		mouse_pos(int button, int x, int y, void *param);
void	init_mandelbrot(t_pos *pos);
void	init_julia(t_pos *pos);
void	mandelbrot_set(void);
void	julia_set(double c_r, double c_i);
void	init_img(t_img *img);
void	ft_putstr(char *str);

#endif
