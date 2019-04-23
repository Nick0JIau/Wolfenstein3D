/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:24:53 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/26 12:24:55 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_pic(int *xx, int *yy, int z)
{
	static int	x;
	static int	y;
	static int	flag;
	static int	flagy;

	while (z < 4)
	{
		if (z == 3)
		{
			flag == 1 ? x++ : x--;
			if (x == 20)
				flag = 0;
			else if (x == -20)
				flag = 1;
			flagy == 1 ? y++ : y--;
			if (y == 10)
				flagy = 0;
			else if (y == -10)
				flagy = 1;
		}
		z++;
	}
	*xx = x;
	*yy = y;
}

void	ft_time(t_global *global)
{
	double		frametime;
	char		*str;
	static int	i = 0;

	global->cam->oldtime = global->cam->time;
	global->cam->time = clock();
	frametime = (global->cam->time - global->cam->oldtime) / 1000000.0;
	str = NULL;
	if (i == 60)
	{
		str = ft_itoa(1.0 / frametime);
		i = 0;
	}
	i++;
	ft_putendl(str);
	free(str);
	global->cam->mspeed = frametime * 5.0 + global->speed;
	global->cam->rspeed = frametime * 3.0;
}

void	ft_draw_ceiling(t_global *global, int y)
{
	y = -1;
	while (++y < global->f->start)
	{
		global->f->curdist = HEIGHT / (2.0 * y - HEIGHT);
		global->f->weight = -global->f->curdist / global->f->distw;
		global->f->curfx = global->f->weight * global->f->floorxw +
		(1.0 - global->f->weight) * global->player->pos_x;
		global->f->curfy = global->f->weight * global->f->flooryw +
		(1.0 - global->f->weight) * global->player->pos_y;
		global->f->ftx = (int)(global->f->curfx * 700) % 700;
		global->f->fty = (int)(global->f->curfy * 700) % 700;
		ft_pixel_put(global, y, ((int*)global->tex->ctex[4])[700 *
			global->f->fty + global->f->ftx]);
	}
}

void	ft_draw_floor(t_global *global, int y)
{
	while (++y < HEIGHT)
	{
		global->f->curdist = HEIGHT / (2.0 * y - HEIGHT);
		global->f->weight = global->f->curdist / global->f->distw;
		global->f->curfx = global->f->weight * global->f->floorxw +
		(1.0 - global->f->weight) * global->player->pos_x;
		global->f->curfy = global->f->weight * global->f->flooryw +
		(1.0 - global->f->weight) * global->player->pos_y;
		global->f->ftx = (int)(global->f->curfx * 700) % 700;
		global->f->fty = (int)(global->f->curfy * 700) % 700;
		ft_pixel_put(global, y, ((int*)global->tex->ctex[5])[700 *
			global->f->fty + global->f->ftx]);
	}
}

void	ft_init_floor(t_global *global, int x, int y, int yh)
{
	if (global->side == 0 && global->cam->ray_dir_x > 0)
	{
		global->f->floorxw = x;
		global->f->flooryw = y + global->tex->wallx;
	}
	else if (global->side == 0 && global->cam->ray_dir_x < 0)
	{
		global->f->floorxw = x + 1.0;
		global->f->flooryw = y + global->tex->wallx;
	}
	else if (global->side == 1 && global->cam->ray_dir_y > 0)
	{
		global->f->floorxw = x + global->tex->wallx;
		global->f->flooryw = y;
	}
	else
	{
		global->f->floorxw = x + global->tex->wallx;
		global->f->flooryw = y + 1.0;
	}
	if (yh < global->f->start)
		ft_draw_ceiling(global, yh);
	else
		ft_draw_floor(global, yh);
}
