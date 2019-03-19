/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:33:55 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/06 19:32:22 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	verbose_intro(t_env *env, char *op, int proc_nbr)
{
	printer(env, 0, "P %4d | %s", proc_nbr, op);
}

void	verbose_outro(t_env *env, int pc, int length)
{
	int		i;

	printer(env, 0, "ADV %d (%#06x -> %#06x)", length, pc, pc + length);
	i = -1;
	while (++i < length)
		printer(env, 0, " %02x", env->arena[(pc + i) % MEM_SIZE]);
	printer(env, 0, " \n");
}

void	arg_verbose_outro(t_env *env, int first_pc, t_arg_type *arg, int op)
{
	int		length;
	int		i;
	int		dir_size;

	if (env->flags & FLAG_VERBOSE)
	{
		dir_size = get_dir_size(op);
		length = 2;
		i = -1;
		while (++i < 3)
		{
			if (arg[i] == T_REG)
				length++;
			else if (arg[i] == T_DIR && dir_size == 0)
				length += 4;
			else if (arg[i] == T_DIR && dir_size == 1)
				length += 2;
			else if (arg[i] == T_IND)
				length += 2;
		}
		verbose_outro(env, first_pc, length);
	}
}
