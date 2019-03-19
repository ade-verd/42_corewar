/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:06:51 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 19:06:19 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays a message for needed rows and columns
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
*/

void	message_resize(t_env *env, int y, int x)
{
	int	i;
	int	j;
	int ymax;
	int xmax;

	i = 0;
	ymax = env->gph->lgd.y + env->gph->lgd.l;
	xmax = env->gph->inf.x + env->gph->inf.c;
	xmax += (env->flags & FLAG_VERBOSE) ? TRMW_MIN : 0;
	attron(COLOR_PAIR(RCOLOR - ERR_COLOR));
	while (i < env->gph->head.l)
	{
		j = 0;
		while (j < x)
			mvprintw(i, j++, " ");
		i++;
	}
	mvprintw(1, 1, "EVERYTHING'S FUCKED UP %C  PLEASE RESIZE THE WINDOW",
		0x1F624);
	if (x < xmax)
		mvprintw(3, 1, "I need at least %d columns %C", xmax - x, 9654);
	if (y < ymax)
		mvprintw(4, 1, "I need at least %d rows %C", ymax - y, 9660);
	attroff(A_BLINK | COLOR_PAIR(RCOLOR - ERR_COLOR));
}

/*
** @brief: Handles terminal resize
**
** @param env: Context structure
*/

void	visu_resize(t_env *env)
{
	int	x;
	int	y;
	int ymax;
	int xmax;

	ymax = env->gph->lgd.y + env->gph->lgd.l;
	xmax = env->gph->inf.x + env->gph->inf.c;
	xmax += (env->flags & FLAG_VERBOSE) ? TRMW_MIN : 0;
	getmaxyx(stdscr, y, x);
	if (y < ymax || x < xmax)
	{
		env->gph->running = PAUSE;
		message_resize(env, y, x);
	}
	else
	{
		clear();
		visu_delwin(env);
		visu_create_windows(env, env->gph);
		visu_display_scales(env->gph);
		visu_display_header(env, env->gph);
		visu_display_legend(env);
		visu_display_boxes(env->gph);
	}
}
