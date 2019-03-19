/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:32:28 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:21:49 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Pc moving basic function
**
** @param proc: Processors structure
** @param arg: Proc's arguments
** @param dir_size: Direct argument size
*/

static void	ft_move(t_proc *proc, t_arg_type arg, int dir_size)
{
	if (arg == T_REG)
		proc->pc++;
	else if (arg == T_DIR && dir_size == 0)
		proc->pc += 4;
	else if (arg == T_DIR && dir_size == 1)
		proc->pc += 2;
	else if (arg == T_IND)
		proc->pc += 2;
}

/*
** @brief: Moves the proc's pc according to the arguments given
**
** @param env: Context structure
** @param proc: Processors structure
** @param arg: Proc's arguments
** @param op: OP code
*/

void		move_pc(t_env *env, t_proc *proc, t_arg_type *arg, int op)
{
	int		i;
	int		argc;
	int		dir_size;

	argc = 0;
	i = -1;
	dir_size = get_dir_size(op);
	while (g_op_tab[++i].op)
		if (g_op_tab[i].op_code == (unsigned int)op)
		{
			argc = g_op_tab[i].argc;
			break ;
		}
	proc->pc += 2;
	if (argc <= 3)
		ft_move(proc, arg[0], dir_size);
	if (argc >= 2)
		ft_move(proc, arg[1], dir_size);
	if (argc == 3)
		ft_move(proc, arg[2], dir_size);
	proc->working = 0;
	visu_movepc(env, proc);
}
