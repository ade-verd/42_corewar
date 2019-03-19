/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:33:43 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 17:47:56 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Getchs one character with the function getch(). Characters getched
**		   aren't displayed on terminal with the function noecho()
**
** @return int: Value returned by the function getch()
*/

int	ft_getch(void)
{
	int	key;

	noecho();
	key = getch();
	echo();
	return (key);
}
