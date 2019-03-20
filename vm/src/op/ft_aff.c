/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:04:36 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/20 20:25:51 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Adds a character in the buffer as many times as the given "size"
**         If 4096 is exceeded, we double the size of the buffer
**
** @param aff: Buffer structure for ft_aff
** @param c: Character to add
** @param size: Number of times to add the character
*/

static void	buffer_add_char(t_buffer *aff, char c, size_t size)
{
	size_t	new_size;

	if ((aff->index + size) >= 4096)
	{
		new_size = 4096;
		while ((aff->index + size) >= new_size)
			new_size *= 2;
		if (!(aff->str = realloc(aff->str, new_size)))
			return ;
	}
	ft_memset(aff->str + aff->index, c, size);
	aff->index += size;
	aff->len += size;
	aff->str[aff->index] = '\0';
}

/*
** @brief: Displays on the standard output the characters's ASCII value
**         given in the register
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_aff(t_env *env, t_proc *proc)
{
	t_arg_type	arg[4];
	int			r;
	char		aff;

	op_intro(proc, OP_AFF, CH_AFF);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (arg[0] != T_REG)
		{
			proc->pc += 3;
			return ;
		}
		proc->pc += 2;
		if ((r = env->arena[proc->pc++ % MEM_SIZE] - 1) < 0 || r >= REG_NUMBER)
			return ;
		aff = proc->reg[r] % 256;
		buffer_add_char(env->aff, aff, 1);
		printer(env, 0, "aff -> added character : |%c|\n", aff);
		visu_movepc(env, proc);
		proc->working = 0;
	}
	else
		proc->charge--;
}
