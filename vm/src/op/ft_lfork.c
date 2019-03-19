/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:44:21 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/27 12:45:24 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Creates a new process. The new process inherits all of its
** 		   father's states
**
** @param env: Context structure
** @param proc: Processors structure
*/

void	ft_lfork(t_env *env, t_proc *proc)
{
	t_proc	*new;
	int		dir;

	op_intro(proc, OP_LFORK, CH_LFORK);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		new = s_proc_fork(env, proc);
		dir = ((env->arena[(proc->pc + 1) % MEM_SIZE] << 8)
			| env->arena[(proc->pc + 2) % MEM_SIZE]);
		if (dir & 0x8000)
			dir = dir - 0xFFFF - 1;
		new->pc = (proc->pc + dir) % MEM_SIZE;
		if (new->pc < 0)
			new->pc += MEM_SIZE;
		printer(env, 0, "P %4d | lfork %d (%d)\n", proc->nbr, dir, new->pc);
		verbose_outro(env, proc->pc, 3);
		proc->pc += 3;
		visu_movepc(env, proc);
		visu_movepc(env, new);
		proc->working = 0;
	}
	else
		proc->charge--;
}
