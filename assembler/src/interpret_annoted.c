/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_annoted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:57:08 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/04 14:11:08 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: Prints header in annoted version
**
** @param env: Context structure
*/

static void	print_header(t_env *env)
{
	ft_printf("Dumping annotated program\n");
	ft_printf("Magic Number: %#08X\n", env->header.magic);
	ft_printf("Program size: %d bytes\n", env->header.prog_size);
	ft_printf("Name:         \"%s\"\n", env->header.prog_name);
	ft_printf("Comment:      \"%s\"\n\n", env->header.comment);
}

/*
** @brief: Outputs an annotated version of the code to stdout
**
** @param env: Context structure
*/

void		interpret_annoted(t_env *env)
{
	t_asm	*asmb;
	char	*lab;

	asmb = env->asmb;
	lab = NULL;
	print_header(env);
	while (asmb)
	{
		print_label(asmb, &lab);
		if (asmb->arg)
		{
			ft_printf("%sPC: %-4d %s", F_YELLOW, asmb->pc, F_NO);
			ft_printf("%4d Bytes %s⇦%s ", asmb->bytes, F_YELLOW, F_NO);
			print_rcode(asmb);
			print_dec(asmb);
			print_hex(asmb);
		}
		if (asmb->next)
			ft_putchar('\n');
		asmb = asmb->next;
	}
}
