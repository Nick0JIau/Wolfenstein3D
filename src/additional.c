/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:02:45 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/26 16:02:47 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_check_draw(t_global *global)
{
	global->f->start = -global->line_h / 2 + HEIGHT / 2;
	if (global->f->start < 0)
		global->f->start = 0;
	global->f->end = global->line_h / 2 + HEIGHT / 2;
	if (global->f->end >= HEIGHT)
		global->f->end = HEIGHT - 1;
}

void	ft_error_load(void)
{
	ft_putendl("Error load resources");
	exit(1);
}

void	ft_empty_map(void)
{
	ft_putendl("Error map");
	exit(1);
}

int		ft_exit(t_global *global)
{
	if (global->music == 1)
		system("killall afplay");
	exit(0);
	return (0);
}
