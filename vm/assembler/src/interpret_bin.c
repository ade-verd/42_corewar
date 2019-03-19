/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:57:08 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/06 16:44:44 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Prints header in binary
**
** @param env: Context structure
*/

static void	print_header(t_env *env)
{
	int	padding;
	int magic;
	int psize;

	padding = 0;
	magic = ft_endian(env->header.magic, 4);
	psize = ft_endian(env->header.prog_size, 4);
	write(env->fd_out, &magic, sizeof(magic));
	write(env->fd_out, &env->header.prog_name, PROG_NAME_LENGTH);
	write(env->fd_out, &padding, 4);
	write(env->fd_out, &psize, sizeof(psize));
	write(env->fd_out, &env->header.comment, COMMENT_LENGTH);
	write(env->fd_out, &padding, 4);
}

/*
** @brief: Writes output program to fd_out in binary
**
** @param env: Context structure
*/

void		interpret_bin(t_env *env)
{
	t_asm	*asmb;
	t_arg	*arg;
	int		val;

	asmb = env->asmb;
	val = 0;
	create_output(env);
	print_header(env);
	while (asmb)
	{
		if (asmb->op_code != -1)
			write(env->fd_out, &asmb->op_code, 1);
		if (asmb->coding && (val = coding_val(asmb)))
			write(env->fd_out, &val, 1);
		arg = asmb->arg;
		while (arg)
		{
			val = ft_endian(arg->val, arg->bytes);
			write(env->fd_out, &val, arg->bytes);
			arg = arg->next;
		}
		asmb = asmb->next;
	}
	ft_printf("Writing output program to %s\n", env->output);
}
