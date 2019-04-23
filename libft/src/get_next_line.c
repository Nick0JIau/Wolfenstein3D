/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:46:51 by ntrusevi          #+#    #+#             */
/*   Updated: 2018/11/15 17:19:55 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_list		*ft_listcpy(t_list **start, int fd)
{
	t_list	*tmp;

	tmp = *start;
	if (tmp)
	{
		while (tmp)
		{
			if ((int)tmp->content_size == fd)
				return (tmp);
			tmp = tmp->next;
		}
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(start, tmp);
	return (tmp);
}

char				*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;

	if (s1 != NULL && s2 != NULL && n != 0)
	{
		str = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (str == NULL)
			return (0);
		ft_strcpy(str, s1);
		ft_strncat(str, s2, (size_t)n);
		return (str);
	}
	return (0);
}

static char			*ft_joinfree(char *tmp, char *buf, int r)
{
	char	*tmp2;

	tmp2 = tmp;
	tmp = ft_strnjoin(tmp, buf, r);
	free(tmp2);
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*list;
	char			*buf;
	t_list			*start;
	int				r;
	char			*tmp;

	buf = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (fd < 0 || !line || BUFF_SIZE < 0 || read(fd, buf, 0) < 0)
		return (-1);
	start = list;
	list = ft_listcpy(&start, fd);
	while (!(ft_strchr(list->content, '\n')) && (r = read(fd, buf, BUFF_SIZE)))
		list->content = ft_joinfree(list->content, buf, r);
	free(buf);
	r = 0;
	while (((char*)list->content)[r] && (((char*)list->content)[r] != '\n'))
		++r;
	*line = ft_strndup(list->content, r);
	if (((char*)list->content)[r] == '\n')
		++r;
	tmp = list->content;
	list->content = ft_strdup(list->content + r);
	free(tmp);
	list = start;
	return (r ? 1 : 0);
}
