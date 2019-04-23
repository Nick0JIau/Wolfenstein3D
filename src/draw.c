/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:15:21 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/16 16:15:23 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_check_texture(t_global *global)
{
	if (global->player->step_x < 0)
		global->tex->tex_n = 0;
	else if (global->player->step_x > 0)
		global->tex->tex_n = 1;
	if (global->side == 1)
	{
		if (global->player->step_y < 0)
			global->tex->tex_n = 2;
		else if (global->player->step_y > 0)
			global->tex->tex_n = 3;
	}
}

void	ft_pixel_put(t_global *global, int y, int color)
{
	int	i;

	i = 0;
	if (global->x >= 0 && global->x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		i = (global->x * 4) + (y * global->size_line);
		global->simg[i] = color;
		global->simg[++i] = color >> global->bits;
		global->simg[++i] = color >> global->bits * 2;
	}
}

void	ft_draw_line(t_global *global, int x, int y_map)
{
	int y;
	int	d;
	int	texy;

	y = -1;
	ft_check_draw(global);
	ft_init_floor(global, x, y_map, y);
	y = global->f->start;
	while (++y <= global->f->end)
	{
		d = y * 256 - HEIGHT * 128 + global->line_h * 128;
		texy = ((d * 700) / global->line_h) / 256;
		if (texy < 0)
			texy = 0;
		global->color = ((int*)global->tex->ctex[global->tex->tex_n])
			[700 * texy + global->tex->tex_x];
		if (global->side == 1 && global->shadow == 1)
			global->color = (global->color >> 1) & 8355711;
		ft_pixel_put(global, y, global->color);
	}
	y--;
	ft_init_floor(global, x, y_map, y);
}

void	ft_fill_x(t_global *global)
{
	ft_check_texture(global);
	if (global->side == 0)
		global->tex->wallx = global->player->pos_y + global->f->distw *
	global->cam->ray_dir_y;
	else
		global->tex->wallx = global->player->pos_x + global->f->distw *
	global->cam->ray_dir_x;
	global->tex->wallx -= floor((global->tex->wallx));
	global->tex->tex_x = (int)(global->tex->wallx * (double)700);
	if (global->side == 0 && global->cam->ray_dir_x > 0)
		global->tex->tex_x = 700 - global->tex->tex_x - 1;
	if (global->side == 1 && global->cam->ray_dir_y < 0)
		global->tex->tex_x = 700 - global->tex->tex_x - 1;
}

void	ft_find_line_h(t_global *global, int map_x, int map_y)
{
	global->line_h = (int)(HEIGHT / global->f->distw);
	ft_fill_x(global);
	ft_draw_line(global, map_x, map_y);
}
