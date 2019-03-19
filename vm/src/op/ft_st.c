/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:02:26 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:19:09 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cw.h>

/*
** @brief: Checks the validity of the parsed arguments
**
** @param arg: Parsed arguments
** @return int
*/

static int	arg_checker(t_arg_type *arg)
{
	if (!(arg[0] & T_REG))
		return (0);
	if (!(arg[1] & (T_REG | T_IND)))
		return (0);
	return (1);
}

/*
** @brief: Stores the specified register content into the other one
**
** @param env: Context structure
** @param proc: Processors structure
*/

static void	reg_part(t_env *env, t_proc *proc)
{
	int		reg1;
	int		reg2;

	reg1 = env->arena[proc->pc++ % MEM_SIZE] - 1;
	reg2 = env->arena[proc->pc++ % MEM_SIZE] - 1;
	proc->reg[reg2] = proc->reg[reg1];
	printer(env, 0, " r%d r%d\n", reg1 + 1, reg2 + 1);
}

/*
** @brief: Stores the specified register content into the "indirect" address
**
** @param env: Context structure
** @param proc: Processors structure
*/

static void	ind_part(t_env *env, t_proc *proc)
{
	int		pc;
	int		reg;
	int		ind;

	reg = env->arena[proc->pc++ % MEM_SIZE] - 1;
	ind = ((env->arena[proc->pc++ % MEM_SIZE] << 8)
		| env->arena[proc->pc++ % MEM_SIZE]);
	if (ind & 0x8000)
		ind = ind - 0xFFFF - 1;
	pc = proc->first_pc + (ind % IDX_MOD);
	if (pc < 0)
		pc = pc % MEM_SIZE + MEM_SIZE;
	env->arena[pc % MEM_SIZE] = proc->reg[reg] >> 24;
	env->arena[(pc + 1) % MEM_SIZE] = (proc->reg[reg] & 0xff0000) >> 16;
	env->arena[(pc + 2) % MEM_SIZE] = (proc->reg[reg] & 0xff00) >> 8;
	env->arena[(pc + 3) % MEM_SIZE] = (proc->reg[reg] & 0xff);
	printer(env, 0, " r%d %d\n", reg + 1, ind);
	visu_colorized(env, proc, 4, pc);
}

/*
** @brief: Executes all the "store" operations acording to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void		ft_st(t_env *env, t_proc *proc)
{
	t_arg_type	arg[4];

	op_intro(proc, OP_ST, CH_ST);
	if (proc->working && !proc->charge)
	{
		proc->first_pc = proc->pc;
		arg_parser(env->arena[(proc->pc + 1) % MEM_SIZE], arg);
		if (!arg_checker(arg) || !reg_checker(env, proc, arg, proc->working))
			return (move_pc(env, proc, arg, proc->working));
		verbose_intro(env, "st", proc->nbr);
		proc->pc += 2;
		arg[1] == T_REG ? reg_part(env, proc) : ind_part(env, proc);
		visu_movepc(env, proc);
		arg_verbose_outro(env, proc->first_pc, arg, proc->working);
		proc->working = 0;
	}
	else
		proc->charge--;
}
