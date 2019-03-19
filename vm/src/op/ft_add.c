/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:01:57 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:17:30 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Checks the validity of the parsed arguments
**
** @param arg: Parsed arguments
** @return int
*/

static int	arg_checker(t_arg_type *arg)
{
	if (arg[0] != T_REG)
		return (0);
	if (arg[1] != T_REG)
		return (0);
	if (arg[2] != T_REG)
		return (0);
	return (1);
}

/*
** @brief: Adds the content of the 1st and 2nd registers into the 3rd one
**
** @param env: Context structure
** @param proc: Processors structure
*/

static void	regs_part(t_env *env, t_proc *proc)
{
	int			reg1;
	int			reg2;
	int			reg3;

	reg1 = env->arena[proc->pc++ % MEM_SIZE] - 1;
	reg2 = env->arena[proc->pc++ % MEM_SIZE] - 1;
	reg3 = env->arena[proc->pc++ % MEM_SIZE] - 1;
	proc->reg[reg3] = proc->reg[reg1] + proc->reg[reg2];
	proc->carry = (proc->reg[reg3] == 0) ? 1 : 0;
	printer(env, 0, " r%d r%d r%d\n", reg1 + 1, reg2 + 1, reg3 + 1);
}

/*
** @brief: Executes all the "add" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_add(t_env *env, t_proc *proc)
{
	t_arg_type	arg[4];

	op_intro(proc, OP_ADD, CH_ADD);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (!arg_checker(arg) || !reg_checker(env, proc, arg, proc->working))
			return (move_pc(env, proc, arg, proc->working));
		verbose_intro(env, "add", proc->nbr);
		proc->pc += 2;
		regs_part(env, proc);
		visu_movepc(env, proc);
		arg_verbose_outro(env, proc->first_pc, arg, proc->working);
		proc->working = 0;
	}
	else
		proc->charge--;
}
