/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:45:27 by rahassin          #+#    #+#             */
/*   Updated: 2019/03/18 22:26:57 by rahassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasm.h"

int					asm_head(int i, unsigned char *buff, int fdo)
{
	int				s;

	s = 0;
	ft_putstr_fd(".name \"", fdo);
	i = 3;
	while (i < 128)
		if (ft_isprint(buff[++i]))
			ft_putchar_fd(buff[i], fdo);
	ft_putstr_fd("\"\n", fdo);
	i += 8;
	s = s * 0x100 + buff[i++];
	s = s * 0x100 + buff[i++];
	s = s * 0x100 + buff[i++];
	s = s * 0x100 + buff[i];
	ft_putstr_fd(".comment \"", fdo);
	while (i < 2047)
		if (ft_isprint(buff[++i]))
			ft_putchar_fd(buff[i], fdo);
	ft_putstr_fd("\"\n\n", fdo);
	return (s);
}

void				asmr(char *file, int len, int i)
{
	unsigned char	buff[2191 + 1];
	int				fd;
	int				fdo;

	if ((fd = open(file, O_RDONLY | O_RDWR | O_NOCTTY | O_NOFOLLOW
					| O_NONBLOCK)) == -1)
	{
		ft_putstr_fd(ERR_FIL, 2);
		return ;
	}
	ft_memset(buff, 0, 2191);
	buff[read(fd, buff, 2191) + 1] = '\0';
	file[len - 4] = '\0';
	file = ft_strcat(file, "R.s\0");
	fdo = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (buff[0] != 0 && buff[1] != 0xea && buff[2] != 0x83 && buff[3] != 0xf3)
	{
		ft_putstr_fd(ERR_MGN, 2);
		return ;
	}
	if (asmr_instr(fd, fdo, asm_head(i, buff, fdo) + 1, 1))
		ft_putstr_fd(ASMR_OK, 2);
	ft_putendl_fd(file, 2);
	close(fd);
	close(fdo);
}
