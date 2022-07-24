#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS   2
#define X_EVENT_KEY_release 3
#define X_EVENT_KEY_EXIT    17

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "mlx_test"

# define IMG_PIXEL_WIDTH 400
# define IMG_PIXEL_HEIGHT 300

#define KEY_ESC  53
#define KEY_Q    12
#define KEY_W    13
#define KEY_E    14
#define KEY_R    15
#define KEY_A    0
#define KEY_S    1
#define KEY_D    2

typedef struct s_param {
    int x;
    int y;
    char    str[3];
}           t_param;

typedef struct s_img{
    void    *img_ptr;
	int		*data;
	int    	width;
    int     height;

	// not needed to understand
	int		size_l;
	int		bpp;
	int		endian;

}        t_img;

typedef struct s_mlx{
    void    *mlx_ptr;
    void    *win;
    t_img   img;
}              t_mlx;

void    param_init(t_param *param)
{
    param->x = 3;
    param->y =4;
    param->str[0] = 'a';
    param->str[1] = 'b';
    param->str[2] = '\0';
}

void    ft_mlx_init(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
}

int     key_press(int keycode, t_param *param)
{
    static int a = 0;

    if (keycode == KEY_W)
        param->x++;
    else if (keycode == KEY_S)
        param->x--;
    else if (keycode == KEY_ESC)
        exit(0);
    printf("x : %d\n", param->x);
    return (0);
}

void    ft_mlx_img_add(t_mlx *mlx)
{
	int	img_width;
	int	img_height;
    mlx->img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/wall_n.xpm", &mlx->img.width, &mlx->img.height);
}

void	ft_mlx_pixel_add(t_mlx *mlx)
{
	int count_w;
	int count_h;

	mlx->img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "/textures/wall_e.xpm", &mlx->img.width, &mlx->img.height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

	count_h = -1;
	while (++count_h < mlx->img.height)
	{
		count_w = -1;
		while (++count_w < mlx->img.width)
		{
			if (count_w % 2)
				mlx->img.data[count_h * mlx->img.width + count_w] = 0xFFFFFF;
			else
				mlx->img.data[count_h * mlx->img.height + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 50, 50);
}



void	using_print()
{    
	printf("==============================\n");
    printf("W key : Add 1 to x.\n");
    printf("S key : Minus 1 to x.\n");
    printf("ESC key : EXIT.\n");
    printf("Other keys : print current.\n");
    printf("==============================\n");
    printf("Current x = 3\n");
}

int main(void)
{
    t_mlx    mlx;
    t_param param;

    param_init(&param);
    ft_mlx_init(&mlx);
	using_print();
	ft_mlx_pixel_add(&mlx);
    mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
    // mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
}