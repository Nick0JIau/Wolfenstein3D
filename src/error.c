/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:25:31 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/18 17:25:32 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_usage(void)
{
	ft_putendl("Usage: ./wolf3d maps/map_file.w3d");
	exit(1);
}

int		ft_check_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (1);
	return (0);
}

int		ft_check_map(t_list *list, char *str, int i)
{
	int		j;

	j = -1;
	while (str[++j])
		if ((str[j] != ' ' && ft_isdigit(str[j]) == 0) || i < 7 || i > 100)
			return (1);
	if ((size_t)i != ft_strlen(list->content) ||
		str[i - 1] == '0' || str[0] == '0' || ft_check_space(str) == 1)
		return (1);
	return (0);
}

void	ft_check_list(t_list *list, char *str)
{
	int		k;
	t_list	*tmp;

	k = -1;
	tmp = list;
	while (str[++k])
	{
		if (str[k] == '0' && str[k] != ' ')
		{
			list = tmp;
			ft_dellst(&list);
			ft_putendl("Error map");
			exit(1);
		}
	}
}

void	ft_valid_map(t_list *list)
{
	int		i;
	char	*str;
	t_list	*tmp;

	tmp = list;
	i = ft_strlen(list->content);
	str = ft_strdup((char*)list->content);
	ft_check_list(list, str);
	free(str);
	while (list)
	{
		str = ft_strdup((char*)list->content);
		if (ft_check_map(list, str, i) == 1)
		{
			list = tmp;
			ft_dellst(&list);
			ft_putendl("Error map");
			exit(1);
		}
		else
			list = list->next;
		free(str);
	}
	ft_check_list(list, str);
}
