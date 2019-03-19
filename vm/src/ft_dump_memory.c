/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:48:18 by oozkaya           #+#    #+#             */
/*   Updated: 2019/03/14 13:01:30 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static char		*ft_fill_hex(char *addr, int nb)
{
	char	*b;
	int		i;

	b = "0123456789abcdef";
	i = 0;
	while (i < 4)
	{
		addr[3 - i] = b[nb % 16];
		nb = nb / 16;
		i++;
	}
	addr[4] = '\0';
	return (addr);
}

static char		*get_termcolor(int color)
{
	if (color == 1)
		return (PLAYER1_FCOLOR);
	if (color == 2)
		return (PLAYER2_FCOLOR);
	if (color == 3)
		return (PLAYER3_FCOLOR);
	if (color == 4)
		return (PLAYER4_FCOLOR);
	if (color == RCOLOR - 1)
		return (PLAYER1_BCOLOR);
	if (color == RCOLOR - 2)
		return (PLAYER2_BCOLOR);
	if (color == RCOLOR - 3)
		return (PLAYER3_BCOLOR);
	if (color == RCOLOR - 4)
		return (PLAYER4_BCOLOR);
	return (F_NO);
}

static void		footer_players(t_env *env)
{
	t_player	*p;
	int			i;
	const char	*colors[] = { PLAYER1_BCOLOR, PLAYER2_BCOLOR, PLAYER3_BCOLOR,
		PLAYER4_BCOLOR, 0 };

	i = 1;
	if ((p = env->player))
		printer(env, 1, "%8s", "");
	while (p)
	{
		printer(env, 1, "%s %s ", colors[i - 1], F_NO);
		printer(env, 1, "Player %d, \"%.33s\"", i, p->header.prog_name);
		if (p->next)
			printer(env, 1, "\t");
		i++;
		p = p->next;
	}
	printer(env, 1, "\n");
}

void			ft_dump_memory(t_env *env)
{
	int		pc;
	int		diiv;
	char	addr[5];

	pc = 0;
	diiv = ft_sqrt(MEM_SIZE) / 2;
	printer(env, 1, "0x%s: ", ft_fill_hex(addr, pc));
	while (pc < MEM_SIZE)
	{
		pc = pc % MEM_SIZE;
		printer(env, 1, "%02x ", env->arena[pc]);
		if ((pc + 1) % diiv == 0)
			printer(env, 1, "\n");
		if ((pc + 1) % diiv == 0 && (pc + 1) < MEM_SIZE)
			printer(env, 1, "0x%s: ", ft_fill_hex(addr, pc));
		pc++;
	}
}

void			ft_dumpc_memory(t_env *env)
{
	int		pc;
	int		diiv;
	char	addr[5];

	pc = 0;
	diiv = ft_sqrt(MEM_SIZE);
	printer(env, 1, "0x%s: ", ft_fill_hex(addr, pc));
	while (pc < MEM_SIZE)
	{
		pc = pc % MEM_SIZE;
		printer(env, 1, "%s", get_termcolor(env->color[pc]));
		printer(env, 1, "%02x%s ", env->arena[pc], F_NO);
		if ((pc + 1) % diiv == 0)
			printer(env, 1, "\n");
		if ((pc + 1) % diiv == 0 && (pc + 1) < MEM_SIZE)
			printer(env, 1, "0x%s: ", ft_fill_hex(addr, pc));
		pc++;
	}
	if (env->flags & (FLAG_VERBOSE | FLAG_SLEEP))
		footer_players(env);
}
