/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:12:38 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:18:46 by oozkaya          ###   ########.fr       */
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
	if (!(arg[0] & (T_DIR | T_IND)))
		return (0);
	if (!(arg[1] & T_REG))
		return (0);
	return (1);
}

/*
** @brief: Loads the "direct" value into the speficied register
**
** @param env: Context structure
** @param proc: Processors structure
*/

static void	dir_part(t_env *env, t_proc *proc)
{
	int		reg;

	reg = env->arena[(proc->pc + 4) % MEM_SIZE] - 1;
	proc->reg[reg] = ((env->arena[proc->pc % MEM_SIZE] << 24)
		| (env->arena[(proc->pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(proc->pc + 2) % MEM_SIZE] << 8)
		| env->arena[(proc->pc + 3) % MEM_SIZE]);
	proc->carry = (proc->reg[reg] == 0) ? 1 : 0;
	proc->pc += 4;
	printer(env, 0, " %d r%d\n", proc->reg[reg], reg + 1);
}

/*
** @brief: Loads bytes from the "inderict" address into the register specified
**
** @param env: Context structure
** @param proc: Processors structure
*/

static void	ind_part(t_env *env, t_proc *proc)
{
	int		reg;
	int		ind;
	int		pc;

	reg = env->arena[(proc->pc + 2) % MEM_SIZE] - 1;
	ind = ((env->arena[proc->pc % MEM_SIZE] << 8)
		| env->arena[(proc->pc + 1) % MEM_SIZE]);
	pc = proc->pc - 2;
	if (ind & 0x8000)
		ind = ind - 0xFFFF - 1;
	pc = pc + ind;
	if (pc < 0)
		pc = pc % MEM_SIZE + MEM_SIZE;
	proc->reg[reg] = ((env->arena[pc % MEM_SIZE] << 24)
		| (env->arena[(pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(pc + 2) % MEM_SIZE] << 8)
		| env->arena[(pc + 3) % MEM_SIZE]);
	proc->carry = (proc->reg[reg] == 0) ? 1 : 0;
	proc->pc += 2;
	printer(env, 0, " %d r%d\n", ind, reg + 1);
}

/*
** @brief: Executes all the "long load" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_lld(t_env *env, t_proc *proc)
{
	t_arg_type	arg[4];

	op_intro(proc, OP_LLD, CH_LLD);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (!arg_checker(arg) || !reg_checker(env, proc, arg, proc->working))
			return (move_pc(env, proc, arg, proc->working));
		verbose_intro(env, "lld", proc->nbr);
		proc->pc += 2;
		arg[0] == T_DIR ? dir_part(env, proc) : ind_part(env, proc);
		proc->pc++;
		visu_movepc(env, proc);
		arg_verbose_outro(env, proc->first_pc, arg, proc->working);
		proc->working = 0;
	}
	else
		proc->charge--;
}
