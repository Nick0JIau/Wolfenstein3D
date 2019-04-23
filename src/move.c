/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:51:02 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/28 17:51:05 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_down(t_global *global)
{
	if (global->map[(int)(global->player->pos_x - global->player->dir_x *
		(global->cam->mspeed + 0.5))][(int)(global->player->pos_y)] == 0)
		global->player->pos_x -= global->player->dir_x * global->cam->mspeed;
	if (global->map[(int)(global->player->pos_x)][(int)
		(global->player->pos_y - global->player->dir_y *
			(global->cam->mspeed + 0.5))] == 0)
		global->player->pos_y -= global->player->dir_y * global->cam->mspeed;
}

void	ft_up(t_global *global)
{
	if (global->map[(int)(global->player->pos_x + global->player->dir_x *
		(global->cam->mspeed + 0.5))][(int)(global->player->pos_y)] == 0)
		global->player->pos_x += global->player->dir_x * global->cam->mspeed;
	if (global->map[(int)(global->player->pos_x)][(int)
		(global->player->pos_y + global->player->dir_y *
			(global->cam->mspeed + 0.5))] == 0)
		global->player->pos_y += global->player->dir_y * global->cam->mspeed;
}

void	ft_rotate_left(t_global *global)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = global->player->dir_x;
	global->player->dir_x = global->player->dir_x *
	cos(-global->cam->rspeed) -
	global->player->dir_y * sin(-global->cam->rspeed);
	global->player->dir_y = old_dir_x * sin(-global->cam->rspeed) +
	global->player->dir_y * cos(-global->cam->rspeed);
	old_plane_x = global->player->plane_x;
	global->player->plane_x = global->player->plane_x *
	cos(-global->cam->rspeed) -
	global->player->plane_y * sin(-global->cam->rspeed);
	global->player->plane_y = old_plane_x * sin(-global->cam->rspeed) +
	global->player->plane_y * cos(-global->cam->rspeed);
}

void	ft_rotate_right(t_global *global)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = global->player->dir_x;
	global->player->dir_x = global->player->dir_x *
	cos(global->cam->rspeed) -
	global->player->dir_y * sin(global->cam->rspeed);
	global->player->dir_y = old_dir_x * sin(global->cam->rspeed) +
	global->player->dir_y * cos(global->cam->rspeed);
	old_plane_x = global->player->plane_x;
	global->player->plane_x = global->player->plane_x *
	cos(global->cam->rspeed) -
	global->player->plane_y * sin(global->cam->rspeed);
	global->player->plane_y = old_plane_x * sin(global->cam->rspeed) +
	global->player->plane_y * cos(global->cam->rspeed);
}

void	ft_loop_move(t_global *global, int *x, int *y)
{
	ft_pic(x, y, 0);
	if (global->player->up)
	{
		ft_up(global);
		ft_pic(x, y, 3);
	}
	if (global->player->down)
	{
		ft_down(global);
		ft_pic(x, y, 3);
	}
	if (global->player->left)
		ft_rotate_left(global);
	if (global->player->right)
		ft_rotate_right(global);
	if (global->player->run)
		global->speed = 0.05;
	if (!global->player->run)
		global->speed = 0.0;
}
