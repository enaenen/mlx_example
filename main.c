#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS   2
#define X_EVENT_KEY_release 3
#define X_EVENT_KEY_EXIT    17

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "mlx_test"

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
    void    *img;
    int     *img_width;
    int     *img_height;
}           t_img;

typedef struct s_mlx{
    void    *mlx;
    void    *win;
    t_img   *img;
}              t_mlx;

void    param_init(t_param *param)
{
    param->x = 3;
    param->y =4;
    param->str[0] = 'a';
    param->str[1] = 'b';
    param->str[2] = '\0';
}

void    ft_mlx_init(t_mlx *_mlx)
{
    _mlx->mlx = mlx_init();
    _mlx->win = mlx_new_window(_mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    _mlx->img = malloc(sizeof(t_img));
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
    mlx->img->img = mlx_xpm_file_to_image(mlx->mlx, "../textures/wall_e.xpm", mlx->img->img_width, mlx->img->img_height);
}

int main(void)
{
    t_mlx    mlx;
    t_param param;

    param_init(&param);
    ft_mlx_init(&mlx);
    ft_mlx_img_add(&mlx);
    printf("==============================\n");
    printf("W key : Add 1 to x.\n");
    printf("S key : Minus 1 to x.\n");
    printf("ESC key : EXIT.\n");
    printf("Other keys : print current.\n");
    printf("==============================\n");
    printf("Current x = 3\n");
    mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 50, 50);
    mlx_loop(mlx.mlx);
}