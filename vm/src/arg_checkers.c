/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:46:59 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/26 16:53:33 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Checks the validity of the parsed arguments (and, or, xor)
**
** @param arg: Parsed arguments
** @return int
*/

int		arg_checker1(t_arg_type *arg)
{
	if (!(arg[0] & (T_REG | T_DIR | T_IND)))
		return (0);
	if (!(arg[1] & (T_REG | T_DIR | T_IND)))
		return (0);
	if (!(arg[2] & T_REG))
		return (0);
	return (1);
}

/*
** @brief: Checks the validity of the parsed arguments (ldi, lldi)
**
** @param arg: Parsed arguments
** @return int
*/

int		arg_checker2(t_arg_type *arg)
{
	if (!(arg[0] & (T_REG | T_DIR | T_IND)))
		return (0);
	if (!(arg[1] & (T_REG | T_DIR)))
		return (0);
	if (!(arg[2] & T_REG))
		return (0);
	return (1);
}

/*
** @brief: Checks the validity of the parsed arguments (sti)
**
** @param arg: Parsed arguments
** @return int
*/

int		arg_checker3(t_arg_type *arg)
{
	if (!(arg[0] & T_REG))
		return (0);
	if (!(arg[1] & (T_REG | T_DIR | T_IND)))
		return (0);
	if (!(arg[2] & (T_REG | T_DIR)))
		return (0);
	return (1);
}
