/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:21:46 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/05 18:22:07 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Handles intro of every operations
**
** @param proc: Processors structure
** @param op: Operation's code
** @param charge: Operation's needed charge
*/

void				op_intro(t_proc *proc, int op, int charge)
{
	if (!proc->working)
	{
		proc->working = op;
		proc->charge = charge;
	}
}

/*
** @brief: Takes op code, reads g_op_tab and returns DIRECT size
**
** @param op_code: OP Code
** @return int: DIR size
*/

int					get_dir_size(int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == (unsigned int)op_code)
			return (g_op_tab[i].dir_size);
		i++;
	}
	return (0);
}

/*
** @brief: Takes the op code, reads g_op_tab and returns his right name
**
** @param op_code: OP code
** @return char*
*/

char				*get_op(int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == (unsigned int)op_code)
			return (g_op_tab[i].op);
		i++;
	}
	return (NULL);
}

/*
** @brief: Returns the right argument parsed from 'to_check'
**
** @param to_check: Arena's pointed case by the pc containing the args
** @return t_arg_type
*/

static t_arg_type	check_all(unsigned char to_check)
{
	if (to_check == REG_CODE)
		return (T_REG);
	else if (to_check == DIR_CODE)
		return (T_DIR);
	else if (to_check == IND_CODE)
		return (T_IND);
	return (0);
}

/*
** @brief: Parses the unsigned char given to get the right arguments
**
** @param to_check: Arena's pointed case by the pc containing the args
** @param arg: Arguments variable to fill
*/

void				arg_parser(unsigned char to_check, t_arg_type *arg)
{
	arg[0] = check_all(to_check >> 6);
	arg[1] = check_all((to_check & 0x30) >> 4);
	arg[2] = check_all((to_check & 0xC) >> 2);
	arg[3] = '\0';
}
