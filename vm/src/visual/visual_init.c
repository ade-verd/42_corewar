/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:21:56 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 18:38:59 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Sets windows positions
**
** @param gph: Graph structure
*/

void	visu_boxes_initial_position(t_gph *gph)
{
	gph->arn.l = ft_sqrt(MEM_SIZE) + 2;
	gph->arn.c = ft_sqrt(MEM_SIZE) * 3 + 1;
	gph->arn.x = 3;
	gph->arn.y = gph->head.y + gph->head.l + 2;
	gph->inf.l = gph->arn.l;
	gph->inf.c = 60;
	gph->inf.x = gph->arn.x + gph->arn.c;
	gph->inf.y = gph->arn.y;
	gph->lgd.l = 6;
	gph->lgd.c = gph->arn.c + gph->inf.c;
	gph->lgd.x = gph->arn.x;
	gph->lgd.y = gph->arn.y + gph->arn.l;
	gph->trm.l = gph->inf.l + gph->lgd.l;
	gph->trm.c = TRMW;
	gph->trm.x = gph->inf.x + gph->inf.c;
	gph->trm.y = gph->arn.y;
}

/*
** @brief: Creates windows: Arena, Info, Legend, Terminal
**
** @param env: Context structure
** @param gph: Graph strucure
*/

void	visu_create_windows(t_env *env, t_gph *gph)
{
	gph->warn = newwin(gph->arn.l, gph->arn.c, gph->arn.y, gph->arn.x);
	if (!gph->warn)
		add_error(env, "Error while creating gph->warn");
	gph->winf = newwin(gph->inf.l, gph->inf.c, gph->inf.y, gph->inf.x);
	if (!gph->winf)
		add_error(env, "Error while creating gph->winf");
	gph->wlgd = newwin(gph->lgd.l, gph->lgd.c, gph->lgd.y, gph->lgd.x);
	if (!gph->wlgd)
		add_error(env, "Error while creating gph->wlgd");
	gph->wtrm = newwin(gph->trm.l, gph->trm.c, gph->trm.y, gph->trm.x);
	if (!gph->wtrm)
		add_error(env, "Error while creating gph->wtrm");
	if (env->err)
		error(env, (char*)__FUNCTION__, 1);
}

/*
** @brief: Displays ordinate's and absciss' scales
**
** @param gph: Graph structure
*/

void	visu_display_scales(t_gph *gph)
{
	int	i;
	int	imax;
	int	x;
	int y;

	i = 0;
	imax = ft_sqrt(MEM_SIZE);
	x = gph->arn.x;
	y = gph->arn.y - 1;
	while (i < imax)
	{
		mvprintw(y, x, " %02d", i++);
		x += 3;
	}
	i = 0;
	x = gph->arn.x - 3;
	y = gph->arn.y + 1;
	while (i < imax)
		mvprintw(y++, x, "%02d", i++);
	mvprintw(gph->arn.y - 1, gph->arn.x - 1, "x");
	mvprintw(gph->arn.y, gph->arn.x - 2, "y");
}

/*
** @brief: Displays boxes
**
** @param gph: Graph structure
*/

void	visu_display_boxes(t_gph *gph)
{
	box(gph->warn, ACS_VLINE, ACS_HLINE);
	mvwprintw(gph->warn, 0, 2, " Arena ");
	box(gph->winf, ACS_VLINE, ACS_HLINE);
	mvwprintw(gph->winf, 0, 2, " Info ");
	box(gph->wlgd, ACS_VLINE, ACS_HLINE);
	mvwprintw(gph->wlgd, 0, 2, " Legend ");
}

/*
** @brief: Initializes nCurses, creates windows, boxes, header, footer, ...
**
** @param env: Context structure
*/

void	visu_init(t_env *env)
{
	setlocale(LC_ALL, "");
	if (env && env->flags & FLAG_NCURSES)
	{
		if (!(env->gph = (t_gph*)malloc(sizeof(t_gph))))
			error(env, (char*)__FUNCTION__, 0);
		env->gph->running = env->goto_cycle ? FW : PAUSE;
		env->gph->cycles_sec = SPEED_DEFAULT;
		initscr();
		curs_set(0);
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		use_default_colors();
		visu_display_header(env, env->gph);
		visu_boxes_initial_position(env->gph);
		visu_display_scales(env->gph);
		visu_create_windows(env, env->gph);
		visu_display_boxes(env->gph);
		visu_display_legend(env);
		visu_init_colors();
		visu_resize(env);
	}
}
