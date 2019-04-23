/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:43 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/15 13:26:45 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int			ft_check_fd(char *av)
{
	int		fd;

	fd = 0;
	if (!(ft_strstr(av, ".w3d")))
	{
		ft_putendl("Invalid file");
		exit(1);
	}
	if ((fd = open(av, O_DIRECTORY)) >= 0)
	{
		ft_putendl("Don't open only directory, please");
		exit(1);
	}
	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_putendl("Error open file");
		exit(1);
	}
	return (fd);
}

void		ft_loop(t_global *global)
{
	mlx_do_key_autorepeatoff(global->mlx);
	mlx_loop_hook(global->mlx, ft_loop_hook, global);
	mlx_hook(global->win, 2, 0, ft_key, global);
	mlx_hook(global->win, 17, 0, ft_exit, global);
	mlx_key_hook(global->win, ft_key_hook, global);
	mlx_loop(global->mlx);
}

void		ft_player_position(t_list *list, t_global *global)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	while (list)
	{
		i = -1;
		str = ft_strsplit(list->content, 32);
		while (str[++i])
		{
			if (str[i][0] == '0')
			{
				global->player->pos_x = j + 0.25;
				global->player->pos_y = i + 0.25;
				ft_free_str(str);
				return ;
			}
		}
		j++;
		list = list->next;
		ft_free_str(str);
	}
	if (global->player->pos_x == 0)
		ft_empty_map();
}

int			**ft_write_map(t_list *list, t_global *global, int i)
{
	int		j;
	int		k;
	char	**str;
	t_list	*tmp;

	i = -1;
	tmp = list;
	while (tmp)
	{
		if (!(global->map[++i] = (int*)malloc(sizeof(int) *
			ft_wordcount(tmp->content, 32))))
			exit(1);
		j = -1;
		k = -1;
		str = ft_strsplit(tmp->content, 32);
		while (str[++k])
		{
			global->map[i][++j] = ft_atoi(str[k]);
		}
		ft_free_str(str);
		tmp = tmp->next;
	}
	ft_player_position(list, global);
	ft_dellst(&list);
	return (global->map);
}

void		ft_open_file(char *av)
{
	int			fd;
	char		*line;
	t_list		*list;
	t_global	*global;
	int			i;

	i = -1;
	fd = ft_check_fd(av);
	while (get_next_line(fd, &line) > 0)
	{
		if (++i == 0)
			list = ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1));
		else
			ft_lstaddback(&list, line, sizeof(char) *
				(ft_strlen(line) + 1));
		free(line);
	}
	if (!list || i < 3 || i > 500)
		ft_empty_map();
	ft_valid_map(list);
	global = ft_init_global(i);
	global->map = ft_write_map(list, global, i);
	ft_loop(global);
	ft_raycast(global);
}
