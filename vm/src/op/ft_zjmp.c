/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:12:28 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:19:42 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Makes a jump at the specified index, if the carry is set to 1.
**         If the carry is 0, zjmp does nothing but consumes the same amount
**         of time
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_zjmp(t_env *env, t_proc *proc)
{
	int	ind;

	op_intro(proc, OP_ZJMP, CH_ZJMP);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		verbose_intro(env, "zjmp", proc->nbr);
		ind = ((env->arena[(proc->pc + 1) % MEM_SIZE] << 8)
			| env->arena[(proc->pc + 2) % MEM_SIZE]);
		if (ind & 0x8000)
			ind = ind - 0xFFFF - 1;
		zjmp_inner_verbose(env, proc, ind);
		if (proc->carry)
		{
			proc->pc = proc->pc + (ind % IDX_MOD);
			if (proc->pc < 0)
				proc->pc = proc->pc % MEM_SIZE + MEM_SIZE;
		}
		else
			proc->pc += 1 + 2;
		visu_movepc(env, proc);
		proc->working = 0;
	}
	else
		proc->charge--;
}
