/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:50:25 by ade-verd          #+#    #+#             */
/*   Updated: 2019/02/20 18:32:11 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief: Returns 1 if the string is a number and stores it in an int pointer
**
** @param str: String
** @param nb: Int pointer
** @return int: 1: is number	0: is NOT number
*/

int		ft_isnumber(char *str, intmax_t *nb)
{
	int		i;

	i = 0;
	if (nb)
		*nb = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (nb)
		*nb = ft_atointmax(str);
	return (1);
}
