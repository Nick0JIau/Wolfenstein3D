/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:37:37 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/15 17:37:39 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_side(t_global *global, int *x, int *y)
{
	if (global->cam->sd_x < global->cam->sd_y)
	{
		global->cam->sd_x += global->cam->dd_x;
		*x += global->player->step_x;
		global->side = 0;
	}
	else
	{
		global->cam->sd_y += global->cam->dd_y;
		*y += global->player->step_y;
		global->side = 1;
	}
}

void	ft_find_wall(t_global *global, int map_x, int map_y)
{
	int		wall;

	global->f->distw = -1;
	wall = 0;
	while (wall == 0)
	{
		ft_side(global, &map_x, &map_y);
		if (global->map[map_x][map_y] > 0)
		{
			wall = 1;
			if (global->side == 0)
				global->f->distw = (map_x - global->player->pos_x +
					(1 - global->player->step_x) / 2) / global->cam->ray_dir_x;
			else
				global->f->distw = (map_y - global->player->pos_y +
					(1 - global->player->step_y) / 2) / global->cam->ray_dir_y;
		}
	}
	ft_find_line_h(global, map_x, map_y);
}

void	ft_calc_step(t_global *global)
{
	if (global->cam->ray_dir_x < 0)
	{
		global->player->step_x = -1;
		global->cam->sd_x = (global->player->pos_x -
			(int)global->player->pos_x) * global->cam->dd_x;
	}
	else
	{
		global->player->step_x = 1;
		global->cam->sd_x = ((int)global->player->pos_x +
			1 - global->player->pos_x) * global->cam->dd_x;
	}
	if (global->cam->ray_dir_y < 0)
	{
		global->player->step_y = -1;
		global->cam->sd_y = (global->player->pos_y -
			(int)global->player->pos_y) * global->cam->dd_y;
	}
	else
	{
		global->player->step_y = 1;
		global->cam->sd_y = ((int)global->player->pos_y +
			1 - global->player->pos_y) * global->cam->dd_y;
	}
}

void	ft_init_ray(t_global *global)
{
	global->cam->cam_x = 2 * global->x / (double)WIDTH - 1;
	global->cam->ray_dir_x = global->player->dir_x +
	global->player->plane_x * global->cam->cam_x;
	global->cam->ray_dir_y = global->player->dir_y +
	global->player->plane_y * global->cam->cam_x;
	global->cam->dd_x = fabs(1 / global->cam->ray_dir_x);
	global->cam->dd_y = fabs(1 / global->cam->ray_dir_y);
}

void	ft_raycast(t_global *global)
{
	double	map_x;
	double	map_y;

	global->x = -1;
	map_x = (int)global->player->pos_x;
	map_y = (int)global->player->pos_y;
	global->cam->mspeed = 0.05;
	global->cam->rspeed = 0.05;
	while (++global->x < WIDTH)
	{
		ft_init_ray(global);
		ft_calc_step(global);
		ft_find_wall(global, map_x, map_y);
	}
}
