/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrusevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 10:53:48 by ntrusevi          #+#    #+#             */
/*   Updated: 2018/11/05 13:38:43 by ntrusevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitesp(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int			ft_atoi(const char *str)
{
	unsigned long long int	result;
	int						sign;
	size_t					i;

	sign = 1;
	i = 0;
	result = 0;
	while (ft_whitesp(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((int)result * sign);
}
