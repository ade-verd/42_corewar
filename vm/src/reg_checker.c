/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:09:57 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:05:46 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Moves pc according to the given arguments
**
** @param env: Context structure
** @param arg: OP arguments
** @param dir_size: Direct size
** @param pc: Proc's pointed address in the arena
** @return int
*/

static int	ft_check(t_env *env, t_arg_type arg, int dir_size, int *pc)
{
	int		reg;

	if (arg == T_REG)
	{
		reg = env->arena[(*pc)++ % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
			return (0);
	}
	else if (arg == T_DIR)
	{
		if (dir_size == 0)
			(*pc) += 4;
		else
			(*pc) += 2;
	}
	else if (arg == T_IND)
		(*pc) += 2;
	return (1);
}

/*
** @brief: Checks the validity of the parsed register
**
** @param env: Context structure
** @param proc: Processors structure
** @param arg: OP arguments
** @param op: OP code
** @return int
*/

int			reg_checker(t_env *env, t_proc *proc, t_arg_type *arg, int op)
{
	int		i;
	int		pc;
	int		argc;
	int		dir_size;

	pc = proc->pc;
	dir_size = get_dir_size(op);
	argc = 0;
	i = -1;
	while (g_op_tab[++i].op)
		if (g_op_tab[i].op_code == (unsigned int)op)
		{
			argc = g_op_tab[i].argc;
			break ;
		}
	pc += 2;
	i = 0;
	while (i < argc)
	{
		if (!ft_check(env, arg[i], dir_size, &pc))
			return (0);
		i++;
	}
	return (1);
}
