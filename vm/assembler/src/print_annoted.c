/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_annoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:43:56 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/04 14:16:58 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Prints label as annoted version
**
** @param asmb: t_asm link
** @param lab: Last label
*/

void	print_label(t_asm *asmb, char **lab)
{
	int	new;

	new = 0;
	if (!*lab && asmb->label)
		new++;
	else if (*lab && asmb->label && ft_strcmp(*lab, asmb->label) != 0)
		new++;
	if (new)
	{
		*lab = asmb->label;
		ft_printf("\n");
		ft_printf("%sPC: %-4d %s", F_CYAN, asmb->pc, F_NO);
		ft_printf("%s%14s%s%s", F_CYAN, "", *lab, F_NO);
		if (asmb->arg)
			ft_printf("\n");
	}
}

/*
** @brief: Prints every argument as Red Code
**
** @param asmb: t_asm link
*/

void	print_rcode(t_asm *asmb)
{
	t_arg	*arg;

	arg = asmb->arg;
	ft_printf(" %-11s", codetoop(asmb->op_code));
	while (arg)
	{
		ft_printf(" | %-16s ", arg->rcode);
		arg = arg->next;
	}
	ft_putchar('\n');
}

/*
** @brief: Prints argument value in base 10 or 16
**
** @param arg: t_arg link
** @param base: base 10 or 16
*/

void	print_arg(t_arg *arg, char base)
{
	if (base == 10)
	{
		if (arg->type == REG_CODE)
			ft_printf(" | %-16d ", arg->val);
		else if (arg->type == IND_CODE)
			ft_printf(" | %-16d ", arg->val);
		else if (arg->type == DIR_CODE)
			ft_printf(" | %-16d ", arg->val);
	}
	else if (base == 16)
	{
		if (arg->type == REG_CODE)
			ft_printf(" | %02X%14s ", arg->val, "");
		else if (arg->type == IND_CODE || arg->dirsize == 1)
			ft_printf(" | %02X %02X %11s", arg->val >> 8, arg->val & 0xFF, "");
		else if (arg->type == DIR_CODE)
		{
			ft_printf(" | %02X ", arg->val >> 24);
			ft_printf("%02X ", (arg->val & 0xFF0000) >> 16);
			ft_printf("%02X ", (arg->val & 0xFF00) >> 8);
			ft_printf("%02X %5s", arg->val & 0xFF, "");
		}
	}
}

/*
** @brief: Prints line as decimal values
**
** @param asmb: t_asm link
*/

void	print_dec(t_asm *asmb)
{
	t_arg	*arg;

	arg = asmb->arg;
	ft_printf("%23s", "");
	ft_printf("%02d ", asmb->op_code);
	if (asmb->coding)
		ft_printf(" | %4d ", coding_val(asmb));
	else
		ft_printf("   %4s ", "");
	while (arg)
	{
		print_arg(arg, 10);
		arg = arg->next;
	}
	ft_putchar('\n');
}

/*
** @brief: Prints line as hexadecimal values
**
** @param asmb: t_asm link
*/

void	print_hex(t_asm *asmb)
{
	t_arg	*arg;

	arg = asmb->arg;
	ft_printf("%23s", "");
	ft_printf("%02X ", asmb->op_code);
	if (asmb->coding)
		ft_printf(" | %2s%02X ", "", coding_val(asmb));
	else
		ft_printf("   %4s ", "");
	while (arg)
	{
		print_arg(arg, 16);
		arg = arg->next;
	}
	ft_putchar('\n');
}
