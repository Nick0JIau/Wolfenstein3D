/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:40:44 by ntrusevi          #+#    #+#             */
/*   Updated: 2019/02/15 13:40:46 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **list, char const *content, size_t content_size)
{
	t_list	*newlist;
	t_list	*tmp;
	t_list	*start;

	if (list != NULL && content != NULL && content_size != 0)
	{
		tmp = *list;
		start = tmp;
		newlist = ft_lstnew(content, content_size);
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = newlist;
		*list = start;
	}
}
