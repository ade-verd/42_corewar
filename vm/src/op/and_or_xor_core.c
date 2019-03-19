/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:45:32 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/26 18:15:40 by ade-verd         ###   ########.fr       */
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

	ret = ((env->arena[proc->pc % MEM_SIZE] << 24)
		| (env->arena[(proc->pc + 1) % MEM_SIZE] << 16)
		| (env->arena[(proc->pc + 2) % MEM_SIZE] << 8)
		| (env->arena[(proc->pc + 3) % MEM_SIZE]));
	proc->pc += 4;
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
	int		ret;
	int		ind;
	int		pc;

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
	if (ret & 0x80000000)
		ret = ret - 0xFFFFFFFF - 1;
	return (ret);
}

/*
** @brief: Applies '&', '|', or '^' in bitwise, according to the operation
**
** @param ret1: 1st element of the bitwise calcul
** @param ret2: 2nd element
** @param op: Bitwise operation specified
** @return int
*/

static int	ope(int a, int b, int op, t_proc *proc)
{
	if (op == OP_AND)
	{
		proc->carry = ((a & b) == 0) ? 1 : 0;
		return (a & b);
	}
	else if (op == OP_OR)
	{
		proc->carry = ((a | b) == 0) ? 1 : 0;
		return (a | b);
	}
	else if (op == OP_XOR)
	{
		proc->carry = ((a ^ b) == 0) ? 1 : 0;
		return (a ^ b);
	}
	proc->carry = 1;
	return (0);
}

/*
** @brief: Executes all the operations ("and", "or" or "xor")
**         according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		and_or_xor_core(t_env *env, t_proc *proc, int op)
{
	t_arg_type	arg[4];
	int			a;
	int			b;

	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (!arg_checker1(arg) || !reg_checker(env, proc, arg, op))
			return (move_pc(env, proc, arg, op));
		verbose_intro(env, get_op(op), proc->nbr);
		proc->pc += 2;
		a = arg_applier(env, proc, arg[0]);
		b = arg_applier(env, proc, arg[1]);
		printer(env, 0, " %d %d r%d\n", a, b, env->arena[proc->pc % MEM_SIZE]);
		proc->reg[env->arena[proc->pc++ % MEM_SIZE] - 1] = ope(a, b, op, proc);
		visu_movepc(env, proc);
		arg_verbose_outro(env, proc->first_pc, arg, op);
		proc->working = 0;
	}
	else
		proc->charge--;
}
