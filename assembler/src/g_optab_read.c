/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_optab_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:56:26 by ade-verd          #+#    #+#             */
/*   Updated: 2018/12/17 17:01:41 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Takes op, reads g_op_tab and returns op_code
**
** @param op: Op as string
** @return int: OP Code
*/

int			optocode(char *op)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op)
	{
		if (ft_strcmp(g_op_tab[i].op, op) == 0)
			return (g_op_tab[i].op_code);
		i++;
	}
	return (0);
}

/*
** @brief: Takes op code, reads g_op_tab and returns op
**
** @param op_code: OP Code
** @return char*: OP
*/

char		*codetoop(unsigned int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == op_code)
			return (g_op_tab[i].op);
		i++;
	}
	return (NULL);
}

/*
** @brief: Takes OP Code, reads g_op_tab and returns octal coding
**
** @param op_code: OP Code
** @return int: Octal Coding 1 or 0
*/

int			got_octalcoding(unsigned int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == op_code)
			return (g_op_tab[i].coding);
		i++;
	}
	return (0);
}

/*
** @brief: Takes op code, reads g_op_tab and returns DIRECT size
**
** @param op_code: OP Code
** @return int: DIR size
*/

int			dir_size(unsigned int op_code)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == op_code)
			return (g_op_tab[i].dir_size);
		i++;
	}
	return (0);
}

/*
** @brief: Takes op code and index, reads g_op_tab and returns arg[index] type
**
** @param op_code: OP Code
** @param index: Argument index
** @return t_arg_type: Arg[index] type
*/

t_arg_type	get_argtype(int op_code, unsigned int index)
{
	int	i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == (unsigned int)op_code)
		{
			if (index < g_op_tab[i].argc)
				return (g_op_tab[i].argv[index]);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}
