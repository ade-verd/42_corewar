/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:21:56 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 19:05:11 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays border around winner
**
** @param env: Context structure
** @param len: Length of prog_name
** @param y: Ordinate
** @param x: Absciss
*/

void		visu_winnerborder(t_env *env, int len, int y, int x)
{
	int		i;
	char	c;

	c = ' ';
	i = -3;
	while (i < (len + 3))
	{
		mvwprintw(env->gph->winf, y - 2, x + i, "%C", c);
		mvwprintw(env->gph->winf, y + 2, x + i, "%C", c);
		i++;
	}
	i = 1;
	while (i < 4)
	{
		mvwprintw(env->gph->winf, (y - 2) + i, x - 2, "%C", c);
		mvwprintw(env->gph->winf, (y - 2) + i, x - 3, "%C", c);
		mvwprintw(env->gph->winf, (y - 2) + i, x + len + 1, "%C", c);
		mvwprintw(env->gph->winf, (y - 2) + i, x + len + 2, "%C", c);
		i++;
	}
}

/*
** @brief: Prints winner
**
** @param env: Context structure
** @param p: Winner
** @param y: Ordinate
** @param x: Absciss
*/

void		visu_print_winner(t_env *env, t_player *p, int y, int x)
{
	int	len;

	len = ft_strlen(p->header.prog_name);
	len = len > (env->gph->inf.c - 10) ? env->gph->inf.c - 10 : len;
	wattron(env->gph->winf, A_BOLD);
	mvwprintw(env->gph->winf, y, x, "%.*s", len, p->header.prog_name);
	wattron(env->gph->winf, COLOR_PAIR(RCOLOR - ft_abs(p->id)));
	visu_winnerborder(env, len, y, x);
	wattroff(env->gph->winf, COLOR_PAIR(RCOLOR - ft_abs(p->id)));
	x = (env->gph->inf.c / 2) - (ft_strlen("Press END to finish") / 2);
	mvwprintw(env->gph->winf, y + 4, x, "%s", "Press END to finish");
	wattroff(env->gph->winf, A_BOLD);
	ft_wrefresh(env);
}

/*
** @brief: Displays winner and handles quit event
**
** @param env: Context structure
** @param p: Winner
*/

void		visu_winner(t_env *env, t_player *p)
{
	int	x;
	int	y;
	int	key;

	if (!(env->flags & FLAG_NCURSES))
		return ;
	y = 59;
	x = (env->gph->inf.c / 2) - (ft_strlen(p->header.prog_name) / 2);
	env->gph->running = STOP;
	visu_resize(env);
	visu_print_winner(env, p, y, x);
	while ((key = ft_getch()) != KEY_END)
	{
		if (key == KEY_RESIZE)
		{
			visu_resize(env);
			env->gph->running = STOP;
			visu_print_winner(env, p, y, x);
		}
		ft_wrefresh(env);
	}
}

/*
** @brief: Deletes windows
**
** @param env: Context structure
*/

void		visu_delwin(t_env *env)
{
	if (env->gph && env->gph->warn)
		delwin(env->gph->warn);
	if (env->gph && env->gph->winf)
		delwin(env->gph->winf);
	if (env->gph && env->gph->wlgd)
		delwin(env->gph->wlgd);
	if (env->gph && env->gph->wtrm)
		delwin(env->gph->wtrm);
}

/*
** @brief: nCurses end
**
** @param env: Context structure
*/

void		visu_end(t_env *env)
{
	if (env && env->flags & FLAG_NCURSES)
	{
		visu_delwin(env);
		if (env->gph)
			ft_memdel((void**)&env->gph);
		endwin();
	}
}
