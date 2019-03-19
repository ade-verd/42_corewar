/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:53:02 by ade-verd          #+#    #+#             */
/*   Updated: 2018/12/13 17:37:11 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief: Returns size of char**
**
** @param tab: Array of char*
** @return int: Size of char**
*/

int	ft_arrstrlen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}
