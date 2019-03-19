/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:24:00 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 18:45:03 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Analyzes arg's red code and tries to returns the type code.
**
** @param arg: t_arg link
** @param op_code: OP Code
** @return int: Return Type Code or 0
*/

int		analyze_nb_bytes(t_arg *arg, unsigned int op_code)
{
	if (!arg || !op_code)
		return (0);
	if (arg->type == REG_CODE)
		return (REG_BITS);
	if (arg->type == IND_CODE)
		return (IND_BITS);
	if (arg->type == DIR_CODE)
		return (dir_size(op_code) ? DIR_BITS2 : DIR_BITS4);
	return (0);
}

/*
** @brief Gets the label position (PC)
**
** @param head: t_asm first link
** @param label: Label as string
** @return int: Returns the label position or -1
*/

int		get_labelpc(t_asm *head, char *label)
{
	t_asm	*asmb;

	asmb = head;
	while (asmb)
	{
		if (asmb->label && label)
			if (ft_strcmp(asmb->label, label) == 0)
				return (asmb->pc);
		asmb = asmb->next;
	}
	return (-1);
}

/*
** @brief Gets the numeric value of an argument
**
** @param env: Context structure
** @param asmb: t_asm link
** @param arg: t_arg link
** @return int: Returrn value
*/

int		get_val(t_env *env, t_asm *asmb, t_arg *arg)
{
	intmax_t	nb;
	char		*str;
	int			labelpc;

	nb = 0;
	labelpc = 0;
	str = arg->rcode;
	if (arg->type == REG_CODE || arg->type == ERR_REG)
		return (ft_atoi(str + 1));
	else if (arg->type == DIR_CODE)
		str++;
	if (str[0] != LABEL_CHAR && ft_isnumber(str, &nb))
		return (nb);
	if (ft_strchr(str, LABEL_CHAR))
		labelpc = get_labelpc(env->asmb, str + 1);
	else
		arg->type = ERR_LEX;
	return (labelpc == -1 ? -1 : labelpc - asmb->pc);
}

/*
** @brief: Counts how many bytes an op takes
**
** @param: t_asm link
** @param arg: t_arg link
** @return int: Returns number of bytes
*/

int		countbytes(t_asm *asmb, t_arg *arg)
{
	int		n;
	int		op;
	int		coding;
	t_arg	*cpy;

	n = 0;
	op = 1;
	coding = 0;
	cpy = arg;
	while (cpy)
	{
		n += cpy->bytes;
		cpy = cpy->next;
	}
	coding = asmb->coding ? 1 : 0;
	return (!arg ? 0 : op + coding + n);
}
