/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_verbose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:33:47 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/14 12:08:57 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	ldi_inner_verbose(t_env *env, int ret1, int ret2, t_proc *proc)
{
	int		sum;
	int		reg;

	sum = ret1 + ret2;
	reg = env->arena[proc->pc % MEM_SIZE];
	printer(env, 0, " %d %d r%d\n", ret1, ret2, reg);
	printer(env, 0, "       | -> load from %d + %d = %d ", ret1, ret2, sum);
}

void	sti_verbose_intro(t_env *env, t_proc *proc)
{
	int		reg;

	verbose_intro(env, "sti", proc->nbr);
	reg = env->arena[(proc->pc + 2) % MEM_SIZE];
	printer(env, 0, " r%d", reg);
}

void	sti_inner_verbose(t_env *env, int ret1, int ret2)
{
	int		sum;

	sum = ret1 + ret2;
	printer(env, 0, " %d %d\n", ret1, ret2);
	printer(env, 0, "       | -> store to %d + %d = %d ", ret1, ret2, sum);
}

void	zjmp_inner_verbose(t_env *env, t_proc *proc, int ind)
{
	if (proc->carry)
		printer(env, 0, " %d OK\n", ind);
	else
	{
		printer(env, 0, " %d FAILED\n", ind);
		verbose_outro(env, proc->pc, 3);
	}
}
