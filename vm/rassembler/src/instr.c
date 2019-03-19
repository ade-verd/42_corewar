/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:34:57 by rahassin          #+#    #+#             */
/*   Updated: 2019/03/13 10:28:59 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasm.h"

unsigned char		*neg_val(int rep, int i, unsigned char *file, int fd)
{
	int				val;

	val = 0;
	while (rep-- > 0)
	{
		file[i] = 255 - file[i];
		i++;
	}
	file[i - 1] += 1;
	ft_putchar_fd('-', fd);
	return (file);
}

int					asmr_arg(int o, unsigned char *file, int i, int fd)
{
	int				rep;
	int				val;

	val = 0;
	rep = o;
	ft_putchar_fd(' ', fd);
	if (o == 3)
	{
		rep = IND_SIZE;
	}
	else if (o == 2)
	{
		if (file[0] != 9 && file[0] != 10 && file[0] != 11 && file[0] != 12
			&& file[0] != 14 && file[0] != 15)
			rep = 4;
		ft_putstr_fd("%", fd);
	}
	else if (o == 1)
		ft_putstr_fd("r", fd);
	file[i] > 127 ? file = neg_val(rep, i, file, fd) : 0;
	while (rep-- > 0)
		val = 0x100 * val + file[i++];
	ft_putnbr_fd(val, fd);
	return (i);
}

int					instr_val(int i, unsigned char *file, int fdo)
{
	t_opc			o;

	o = *(t_opc*)&file[i++];
	if (o.op3)
		i = asmr_arg(o.op3, file, i, fdo);
	if (o.op2 != 0)
		ft_putchar_fd(',', fdo);
	if (o.op2)
		i = asmr_arg(o.op2, file, i, fdo);
	if (o.op1 != 0)
		ft_putchar_fd(',', fdo);
	if (o.op1)
		i = asmr_arg(o.op1, file, i, fdo);
	ft_putchar_fd('\n', fdo);
	return (i);
}

int					asmr_instr(int fd, int fdo, int s, int i)
{
	unsigned char	*file;

	if (!(file = (unsigned char*)malloc(sizeof(unsigned char) * s + 1)))
		return (0);
	file[read(fd, file, s) + 1] = '\0';
	while (i < s)
	{
		if (!file || file[i] >= 17)
		{
			ft_putstr_fd(ERR_INS, 2);
			return (0);
		}
		ft_putstr_fd(g_op_tab[file[i++] - 1].op, fdo);
		file[0] = g_op_tab[file[i - 1] - 1].op_code;
		if (g_op_tab[file[i - 1] - 1].coding == 1)
			i = instr_val(i, file, fdo);
		else
		{
			i = asmr_arg(2, file, i, fdo);
			ft_putchar_fd('\n', fdo);
		}
		file[0] = 0;
	}
	ft_memdel((void**)&file);
	return (1);
}
