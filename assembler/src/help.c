/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:43:44 by ade-verd          #+#    #+#             */
/*   Updated: 2018/12/17 15:30:56 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief: help and flags debug
*/

void	help(void)
{
	ft_putstr("Usage\t./asm [-adfh] <file.s>\n");
	ft_putstr("Reads the assembly’s code processed from the file.s ");
	ft_putstr("and writes the resulting bytecode in file.cor\n");
	ft_putstr("——————\n");
	ft_printf("%3s\t%s", "-aA", "[Annoted] Instead of creating a .cor file, ");
	ft_putstr("outputs an annotated version of the code to stdout\n");
	ft_printf("%3s\t%s\n", "-dD", "[Debug] Displays debug strings");
	ft_printf("%3s\t%s\n", "-fF", "[Flags] Displays flags details in binary");
	ft_printf("%3s\t%s\n", "-hH", "[Help] Displays this help");
}

/*
** @brief: Prints flags activated with binary display
**
** @param env: Context structure
*/

void	flag_debug(t_env *env)
{
	help();
	ft_putchar('\n');
	ft_printf("      \tAFDH\n");
	ft_printf("flags:\t%04b\n", env->flags);
	if (env && (env->flags & FLAG_HELP) != 0)
		error(env, "NO", 0);
	else
		ft_putchar('\n');
}

/*
** @brief: Manages functions help() and flag_debug()
**
** @param env: Context structure
*/

void	deal_help_debug(t_env *env)
{
	if (env && (env->flags & FLAG_DEBUG_FLAGS) != 0)
		flag_debug(env);
	else if (env && (env->flags & FLAG_HELP) != 0)
	{
		help();
		error(env, "NO", 0);
	}
}
