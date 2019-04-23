/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:50:39 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/18 14:50:40 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_loop_hook(t_global *global)
{
	int	x;
	int	y;

	ft_loop_move(global, &x, &y);
	ft_raycast(global);
	ft_time(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img, 0, 0);
	mlx_put_image_to_window(global->mlx, global->win,
		global->tex->tex[6], 600 + x, 500 + y);
	mlx_put_image_to_window(global->mlx, global->win,
		global->tex->tex[7], 0, 0);
	mlx_put_image_to_window(global->mlx, global->win,
		global->tex->tex[8], WIDTH / 2 - 10 + x, HEIGHT / 2 + y + 50);
	return (0);
}

void	ft_music(t_global *global)
{
	if (global->music == 0)
		global->music = 1;
	else if (global->music == 1)
		global->music = 0;
	if (global->music == 1)
		system("afplay ./res/sound.mp3&");
	else if (global->music == 0)
		system("killall afplay");
}

void	ft_key_move(int key, t_global *global)
{
	if (key == ESC)
	{
		if (global->music == 1)
			system("killall afplay");
		mlx_destroy_window(global->mlx, global->win);
		exit(0);
	}
	if (key == UP)
		global->player->up = !global->player->up;
	if (key == DOWN)
		global->player->down = !global->player->down;
	if (key == LEFT)
		global->player->left = !global->player->left;
	if (key == RIGHT)
		global->player->right = !global->player->right;
	if (key == SHIFT)
		global->player->run = !global->player->run;
}

int		ft_key_hook(int key, t_global *global)
{
	ft_key_move(key, global);
	return (0);
}

int		ft_key(int key, t_global *global)
{
	if (key == M)
		ft_music(global);
	if (key == ALT)
	{
		if (global->shadow == 0)
			global->shadow = 1;
		else if (global->shadow == 1)
			global->shadow = 0;
	}
	if (key == 24)
		global->bits += 8;
	ft_key_move(key, global);
	return (0);
}
