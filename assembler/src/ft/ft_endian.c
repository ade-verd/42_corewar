/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:16:42 by ade-verd          #+#    #+#             */
/*   Updated: 2019/02/26 18:01:54 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief: Swipes the n bytes to convert from Big endian to Little endian and
** vise versa
** @param nb: Bytes to convert
** @param bytes: Number of bytes
** @return int: Converted bytes
*/

unsigned int	ft_endian(unsigned int nb, char bytes)
{
	if (bytes == 1)
		return (nb & 0xff);
	if (bytes == 2)
		return (((nb >> 8) & 0xff) | ((nb << 8) & 0xff00));
	if (bytes == 3)
		return (((nb >> 16) & 0xff) | (nb & 0xff00) | ((nb << 16) & 0xff0000));
	return (((nb >> 24) & 0xff)
		| ((nb << 8) & 0xff0000)
		| ((nb >> 8) & 0xff00)
		| ((nb << 24) & 0xff000000));
}
