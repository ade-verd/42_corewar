/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:19:20 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 12:47:29 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Removes comments
**
** @param str: Line
** @param seperator: Comment char separator
** @return char*: str with comments replaced by whitespaces.
*/

char	*ft_del_comments(char *str, char seperator)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != seperator)
		i++;
	while (str[i])
	{
		str[i] = ' ';
		i++;
	}
	return (str);
}
