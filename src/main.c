/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:07:35 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/11 16:07:36 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void		ft_init_additional(t_global *global, int w, int h)
{
	if (!(global->tex->tex[5] = mlx_xpm_file_to_image(global->mlx,
		"./res/floor.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[6] = mlx_xpm_file_to_image(global->mlx,
		"./res/gun.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[7] = mlx_xpm_file_to_image(global->mlx,
		"./res/hp.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[8] = mlx_xpm_file_to_image(global->mlx,
		"./res/target.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[3] = mlx_xpm_file_to_image(global->mlx,
		"./res/wall_wood.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[4] = mlx_xpm_file_to_image(global->mlx,
		"./res/beton.xpm", &w, &h)))
		ft_error_load();
	global->music = 0;
	global->speed = 0.0;
}

void		ft_fill_texture(t_global *global)
{
	int			bpp;
	int			sl;
	int			end;
	int			w;
	int			h;

	if (!(global->tex = (t_tex*)malloc(sizeof(t_tex))))
		exit(1);
	global->tex->tex = (void**)malloc(sizeof(void*) * TEX + 1);
	global->tex->ctex = (char**)malloc(sizeof(char*) * TEX + 1);
	if (!(global->tex->tex[0] = mlx_xpm_file_to_image(global->mlx,
		"./res/wall_brick.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[1] = mlx_xpm_file_to_image(global->mlx,
		"./res/wall_metal.xpm", &w, &h)))
		ft_error_load();
	if (!(global->tex->tex[2] = mlx_xpm_file_to_image(global->mlx,
		"./res/wall_stone.xpm", &w, &h)))
		ft_error_load();
	ft_init_additional(global, w, h);
	w = -1;
	while (++w < TEX)
		global->tex->ctex[w] = mlx_get_data_addr(global->tex->tex[w],
			&bpp, &sl, &end);
}

t_player	*ft_init_player(void)
{
	t_player	*player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		exit(1);
	player->pos_x = 0;
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->up = 0;
	player->down = 0;
	player->left = 0;
	player->right = 0;
	player->run = 0;
	return (player);
}

t_global	*ft_init_global(int i)
{
	t_global	*global;

	if (!(global = (t_global*)malloc(sizeof(t_global))))
		exit(1);
	if (!(global->map = (int**)malloc(sizeof(int*) * i)))
		exit(1);
	global->mlx = mlx_init();
	global->img = mlx_new_image(global->mlx, WIDTH, HEIGHT);
	global->simg = mlx_get_data_addr(global->img, &global->bpp,
		&global->size_line, &global->endian);
	global->win = mlx_new_window(global->mlx, WIDTH, HEIGHT, TITTLE);
	global->time = 0;
	global->old_time = 0;
	global->side = 0;
	global->player = ft_init_player();
	if (!(global->cam = (t_cam*)malloc(sizeof(t_cam))))
		exit(1);
	global->cam->oldtime = 0.0;
	global->cam->time = 0.0;
	if (!(global->f = (t_floor*)malloc(sizeof(t_floor))))
		exit(1);
	global->shadow = 1;
	global->bits = 8;
	ft_fill_texture(global);
	return (global);
}

int			main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_open_file(av[1]);
	}
	else
		ft_usage();
	return (0);
}
