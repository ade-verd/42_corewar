/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:41:48 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/14 11:33:24 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Checks if string is a (left)label ended by LABEL_CHAR
**
** @param str: String
** @return int: Returns LABEL_CODE in case of success, or 0
*/

int				is_llabel(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == LABEL_CHAR)
		return (LABEL_CODE);
	return (0);
}

/*
** @brief: Checks if string is an op.
**
** @param str: String
** @return int: Returns OP_CODE or -1. If !str, the function returns 0
*/

int				is_op(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (g_op_tab[i].op)
	{
		if (ft_strcmp(g_op_tab[i].op, str) == 0)
			return (OP_CODE);
		i++;
	}
	return (-1);
}

/*
** @brief: Takes a string as RedCode and returns the type code
**
** @param str: String (Red Code)
** @return int: Type code
*/

int				wh_type(char *str)
{
	intmax_t	code;
	int			ret;

	code = 0;
	ret = 0;
	if (!str)
		return (-1);
	if ((code = is_llabel(str)))
		ret = code;
	if ((code = is_op(str)))
		ret = code;
	if (*str == DIRECT_CHAR)
		ret = DIR_CODE;
	if (*str == 'r' && ft_isnumber(str + 1, 0))
	{
		if (ft_atoi(str + 1) >= 1 && ft_atoi(str + 1) <= REG_NUMBER)
			ret = REG_CODE;
		else
			ret = ERR_REG;
	}
	if (*str == LABEL_CHAR || ft_isnumber(str, &code))
		ret = IND_CODE;
	return (ret);
}

/*
** @brief: Take a t_asm link in parameter (an OP) and return a coding byte
** corresponding each argument type.
**
** @param asmb: t_asm link corresponding an op
** @return unsigned char: Coding byte
*/

unsigned char	coding_val(t_asm *asmb)
{
	t_arg			*arg;
	unsigned char	coding;
	unsigned char	bits;

	arg = NULL;
	coding = 0;
	bits = 8;
	if (asmb)
		arg = asmb->arg;
	while (arg)
	{
		coding = coding << 2;
		bits -= 2;
		coding = coding | arg->type;
		arg = arg->next;
	}
	while (bits)
	{
		coding = coding << 2;
		bits -= 2;
	}
	return (coding);
}

unsigned int	code2type(unsigned int code)
{
	if (code == REG_CODE)
		return (T_REG);
	if (code == DIR_CODE)
		return (T_DIR);
	if (code == IND_CODE)
		return (T_IND);
	return (code);
}
