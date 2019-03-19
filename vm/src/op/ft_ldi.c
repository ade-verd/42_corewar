/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:37:48 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/27 16:16:53 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Returns the "direct" value
**
** @param env: Context structure
** @param proc: Processors structure
** @return int
*/

static int	dir_part(t_env *env, t_proc *proc)
{
	int		ret;

	ret = ((env->arena[proc->pc % MEM_SIZE] << 8)
		| env->arena[(proc->pc + 1) % MEM_SIZE]);
	if (ret & 0x8000)
		ret = ret - 0xFFFF - 1;
	proc->pc += 2;
	return (ret);
}

/*
** @brief: Returns bytes from the "inderict" address
**
** @param env: Context structure
** @param proc: Processors structure
** @param initial_pc: Initial pc of this operation
** @return int
*/

static int	ind_part(t_env *env, t_proc *proc)
{
	int				ret;
	int				ind;
	int				pc;

	ind = ((env->arena[proc->pc % MEM_SIZE] << 8)
		| env->arena[(proc->pc + 1) % MEM_SIZE]);
	if (ind & 0x8000)
		ind = ind - 0xFFFF - 1;
	pc = proc->first_pc + (ind % IDX_MOD);
	if (pc < 0)
		pc = pc % MEM_SIZE + MEM_SIZE;
	ret = ((env->arena[pc % MEM_SIZE] << 24)
		| (env->arena[(pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(pc + 2) % MEM_SIZE] << 8)
		| env->arena[(pc + 3) % MEM_SIZE]);
	if (ret & 0x80000000)
		ret = ret - 0xFFFFFFFF - 1;
	proc->pc += 2;
	return (ret);
}

/*
** @brief: Returns the right content according to the 1st, then 2nd, argument
**
** @param env: Context structure
** @param proc: Processors structure
** @param arg: 1st or 2nd argument to work on
** @param initial_pc: Initial pc of this operation
** @return int
*/

static int	arg_applier(t_env *env, t_proc *proc, t_arg_type arg)
{
	int		ret;
	int		reg;

	ret = 0;
	if (arg == T_REG)
	{
		reg = env->arena[proc->pc++ % MEM_SIZE] - 1;
		ret = proc->reg[reg];
	}
	else if (arg == T_DIR)
		ret = dir_part(env, proc);
	else if (arg == T_IND)
		ret = ind_part(env, proc);
	return (ret);
}

/*
** @brief: Adds the found numbers and then loads the right register
**
** @param env: Context structure
** @param proc: Processors structure
** @param initial_pc: Initial pc of this operation
** @param sum: Sum of the 2 arguments found
*/

static void	add_load(t_env *env, t_proc *proc, int sum)
{
	int				pc;
	int				reg;

	reg = env->arena[proc->pc++ % MEM_SIZE] - 1;
	pc = proc->first_pc + (sum % IDX_MOD);
	if (pc < 0)
		pc = pc % MEM_SIZE + MEM_SIZE;
	proc->reg[reg] = ((env->arena[pc % MEM_SIZE] << 24)
		| (env->arena[(pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(pc + 2) % MEM_SIZE] << 8)
		| env->arena[(pc + 3) % MEM_SIZE]);
	printer(env, 0, "(with pc and mod %d)\n", pc);
}

/*
** @brief: Executes all the "ldi" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_ldi(t_env *env, t_proc *proc)
{
	t_arg_type	arg[4];
	int			ret1;
	int			ret2;

	op_intro(proc, OP_LDI, CH_LDI);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (!arg_checker2(arg) || !reg_checker(env, proc, arg, proc->working))
			return (move_pc(env, proc, arg, proc->working));
		verbose_intro(env, "ldi", proc->nbr);
		proc->pc += 2;
		ret1 = arg_applier(env, proc, arg[0]);
		ret2 = arg_applier(env, proc, arg[1]);
		ldi_inner_verbose(env, ret1, ret2, proc);
		add_load(env, proc, ret1 + ret2);
		visu_movepc(env, proc);
		arg_verbose_outro(env, proc->first_pc, arg, proc->working);
		proc->working = 0;
	}
	else
		proc->charge--;
}
