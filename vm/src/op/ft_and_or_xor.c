/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:46:02 by oozkaya           #+#    #+#             */
/*   Updated: 2019/02/25 16:53:20 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Executes all the "and" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void	ft_and(t_env *env, t_proc *proc)
{
	if (!proc->working)
	{
		proc->working = OP_AND;
		proc->charge = CH_AND;
	}
	and_or_xor_core(env, proc, proc->working);
}

/*
** @brief: Executes all the "or" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void	ft_or(t_env *env, t_proc *proc)
{
	if (!proc->working)
	{
		proc->working = OP_OR;
		proc->charge = CH_OR;
	}
	and_or_xor_core(env, proc, proc->working);
}

/*
** @brief: Executes all the "xor" operations according to the parameters
**
** @param env: Context structure
** @param proc: Processors structure
*/

void	ft_xor(t_env *env, t_proc *proc)
{
	if (!proc->working)
	{
		proc->working = OP_XOR;
		proc->charge = CH_XOR;
	}
	and_or_xor_core(env, proc, proc->working);
}
