/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_colorized.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:18:32 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 10:50:30 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Initialized pairing colors
*/

void	visu_init_colors(void)
{
	start_color();
	init_pair(1, PLAYER1_COLOR, COLOR_BLACK);
	init_pair(RCOLOR - 1, COLOR_BLACK, PLAYER1_COLOR);
	init_pair(2, PLAYER2_COLOR, COLOR_BLACK);
	init_pair(RCOLOR - 2, COLOR_BLACK, PLAYER2_COLOR);
	init_pair(3, PLAYER3_COLOR, COLOR_BLACK);
	init_pair(RCOLOR - 3, COLOR_BLACK, PLAYER3_COLOR);
	init_pair(4, PLAYER4_COLOR, COLOR_BLACK);
	init_pair(RCOLOR - 4, COLOR_BLACK, PLAYER4_COLOR);
	init_pair(NORMAL_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(RCOLOR - NORMAL_COLOR, COLOR_BLACK, COLOR_WHITE);
	init_pair(ERR_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(RCOLOR - ERR_COLOR, COLOR_WHITE, COLOR_RED);
}

/*
** @brief: Gets the corresponding color's player
**		   Nota: Colors are paired with player's id
**
** @param env: Context structure
** @param reg0: t_proc*->reg[0] corresponding to t_player*->nplayer
** @return int: Color pairing number
*/

int		get_playercolor(t_env *env, int reg0)
{
	t_player	*p;

	p = env->player;
	while (p)
	{
		if (p->nplayer == (unsigned int)reg0)
			return (ft_abs(p->id));
		p = p->next;
	}
	return (NORMAL_COLOR);
}

/*
** @brief: Applies a specific color from pc to (pc + size - 1)
**
** @param env: Context structure
** @param p: Process
** @param size: Applies the color on SIZE bytes
** @param pc: Applies the color from pc
*/

void	visu_colorized(t_env *env, t_proc *p, int size, unsigned int pc)
{
	int				i;
	int				color;
	unsigned int	position;

	if (!(env->flags & (FLAG_NCURSES | FLAG_DUMPC | FLAG_SLEEP)))
		return ;
	i = 0;
	color = get_playercolor(env, p->reg[0]);
	while (i < size)
	{
		position = pc + i;
		env->color[position % MEM_SIZE] = color;
		i++;
	}
}

/*
** @brief: Kills a pc. Removes eventual background color
**
** @param env: Context structure
** @param p: Process
*/

void	visu_killpc(t_env *env, t_proc *p)
{
	if (!(env->flags & (FLAG_NCURSES | FLAG_DUMPC | FLAG_SLEEP)))
		return ;
	if (env->color[p->pc] >= RCOLOR - MAX_PLAYERS)
		env->color[p->pc] = ft_abs(env->color[p->pc] - RCOLOR);
}

/*
** @brief: Moves the pc's proc on the env->color table.
**		   Assuming that a t_proc* contains `first_pc` and `pc`, which are
**		   respectively `oldpc` and `newpc`,
**		   The color of `oldpc` is set without background color, and
**		   The color of `newpc` is set with a background color.
**
** @param env: Context structure
** @param p: Process
*/

void	visu_movepc(t_env *env, t_proc *p)
{
	unsigned int	oldpc;
	unsigned int	newpc;

	if (!(env->flags & (FLAG_NCURSES | FLAG_DUMPC | FLAG_SLEEP)))
		return ;
	oldpc = p->first_pc % MEM_SIZE;
	newpc = p->pc % MEM_SIZE;
	if (env->color[oldpc] >= RCOLOR - MAX_PLAYERS)
		env->color[oldpc] = ft_abs(env->color[oldpc] - RCOLOR);
	if (env->arena[newpc])
		env->color[newpc] = RCOLOR - env->color[newpc];
}
