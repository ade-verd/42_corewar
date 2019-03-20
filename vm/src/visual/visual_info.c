/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:47:02 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/20 18:29:12 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays and truncates player name
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
** @param p: Corresponding player
*/

void		visu_plyr_name(t_env *env, int *y, int x, t_player *p)
{
	int		i;
	int		max;
	char	*name;

	i = 0;
	max = 43;
	name = p->header.prog_name;
	x += 3;
	mvwprintw(env->gph->winf, *y, x, "Player %d: ", ft_abs(p->id));
	x += 10;
	while (name[i] && max--)
	{
		if (name[i] == '\n')
		{
			mvwprintw(env->gph->winf, (*y)++, x, "%c", '~');
			return ;
		}
		mvwprintw(env->gph->winf, *y, x++, "%c", name[i]);
		i++;
	}
	(*y)++;
}

/*
** @brief: Displays Nplayer identification
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
** @param hex: Hexadecimal number identification (t_player*->nplayer)
*/

void		visu_plyr_id(t_env *env, int *y, int x, unsigned int hex)
{
	mvwprintw(env->gph->winf, (*y)++, x + 5,
		"Idenfication:         %02X %02X %02X %02X",
		(hex & 0xff000000) >> 24,
		(hex & 0xff0000) >> 16,
		(hex & 0xff00) >> 8,
		hex & 0xff);
}

/*
** @brief: Displays every players
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
*/

void		visu_info_plyr(t_env *env, int *y, int x)
{
	t_player	*p;
	int			z;

	p = env->player;
	*y += 4;
	while (env && p)
	{
		z = *y;
		wattron(env->gph->winf, COLOR_PAIR(RCOLOR - ft_abs(p->id)));
		while (z < (*y + 5))
			mvwprintw(env->gph->winf, z++, x, " ");
		wattroff(env->gph->winf, COLOR_PAIR(RCOLOR - ft_abs(p->id)));
		visu_plyr_name(env, y, x, p);
		visu_plyr_id(env, y, x, p->nplayer);
		mvwprintw(env->gph->winf, (*y)++, x + 5,
			"Processes:               %8d", p->procs);
		mvwprintw(env->gph->winf, (*y)++, x + 5,
			"Last live:               %8d", p->last_live);
		mvwprintw(env->gph->winf, *y, x + 5, "Lives in current period: %8d",
			p->lives_curr);
		(*y) += 2;
		p = p->next;
	}
}

/*
** @brief: Displays status
**
** @param env: Context structure
** @param winf: Info Window
** @param y: Ordinate
** @param x: Absciss
*/

static void	visu_status(t_env *env, WINDOW *winf, int *y, int x)
{
	if (env->gph->running == RUN)
		mvwprintw(winf, (*y)++, x, "%C   RUNNING", 9654);
	else if (env->gph->running == FW)
		mvwprintw(winf, (*y)++, x, "%C %C FORWARD", 9654, 9654);
	else if (env->gph->running == PAUSE)
		mvwprintw(env->gph->winf, (*y)++, x, "%C %C PAUSED ", 9612, 9612);
	else if (env->gph->running == STOP)
		mvwprintw(env->gph->winf, (*y)++, x, "%C   FINISHED", 127937);
}

/*
** @brief: Displays infos
**
** @param env: Context structure
** @param winf: Info window
*/

void		visu_info(t_env *env, WINDOW *winf)
{
	int x;
	int	y;

	x = 2;
	y = 2;
	wattron(winf, A_BOLD);
	visu_status(env, winf, &y, x);
	mvwprintw(winf, y += 2, x, "Speed:            %5d", env->gph->cycles_sec);
	mvwprintw(winf, y += 2, x, "Cycle:            %5d", env->cycle);
	mvwprintw(winf, y += 2, x, "Processes:        %5d", env->nbproc);
	visu_info_plyr(env, &y, x);
	visu_currlive_brkdown(env, &y, x);
	visu_lastlive_brkdown(env, &y, x);
	mvwprintw(winf, y += 2, x, "CYCLE TO DIE:     %5d", env->cycle_to_die);
	mvwprintw(winf, y += 2, x, "CYCLE DELTA:      %5d", CYCLE_DELTA);
	mvwprintw(winf, y += 2, x, "NBR LIVE (%d):    %5d", NBR_LIVE,
		env->nbr_live);
	mvwprintw(winf, y += 2, x, "MAX CHECKS:       %5d", env->max_checks);
	wattroff(winf, A_BOLD);
}
