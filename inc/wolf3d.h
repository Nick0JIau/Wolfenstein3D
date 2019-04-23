/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:04:24 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/11 16:04:26 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <string.h>

# define WIDTH	1200
# define HEIGHT	800
# define TEXW	64
# define TEXH	64
# define TITTLE	"Wolf3D"
# define TEX	9
# define M		46
# define SHIFT	257
# define ALT	261

# define ESC	53
# define UP		13
# define DOWN	1
# define LEFT	0
# define RIGHT	2

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		step_x;
	double		step_y;
	char		up;
	char		down;
	char		left;
	char		right;
	char		run;
}				t_player;

typedef struct	s_cam
{
	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		sd_x;
	double		sd_y;
	double		dd_x;
	double		dd_y;
	double		mspeed;
	double		rspeed;
	double		oldtime;
	double		time;
}				t_cam;

typedef struct	s_tex
{
	void		**tex;
	char		**ctex;
	int			tex_x;
	int			tex_n;
	double		wallx;
}				t_tex;

typedef struct	s_floor
{
	double		floorxw;
	double		flooryw;
	double		distw;
	double		distp;
	double		curdist;
	double		weight;
	double		curfx;
	double		curfy;
	int			ftx;
	int			fty;
	int			start;
	int			end;
}				t_floor;

typedef struct	s_struct
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*simg;
	int			bpp;
	int			size_line;
	int			endian;
	int			**map;
	int			x;
	int			side;
	int			line_h;
	int			color;
	int			music;
	int			shadow;
	int			bits;
	double		time;
	double		old_time;
	double		ftime;
	double		speed;
	t_player	*player;
	t_cam		*cam;
	t_tex		*tex;
	t_floor		*f;
}				t_global;

void			ft_open_file(char *av);
void			ft_usage(void);
void			ft_valid_map(t_list *list);
void			ft_empty_map(void);
void			ft_error_load(void);
void			ft_free_str(char **str);
void			ft_time(t_global *global);
void			ft_pic(int *xx, int *yy, int z);
void			ft_loop_move(t_global *global, int *x, int *y);
int				ft_key(int key, t_global *global);
int				ft_key_hook(int key, t_global *global);
int				ft_exit(t_global *global);
int				ft_loop_hook(t_global *global);
t_global		*ft_init_global(int i);
void			ft_raycast(t_global *global);
void			ft_find_line_h(t_global *global, int map_x, int map_y);
void			ft_init_floor(t_global *global, int x, int y, int yh);
void			ft_pixel_put(t_global *global, int y, int color);
void			ft_check_draw(t_global *global);
void			ft_key_move(int key, t_global *global);

#endif
