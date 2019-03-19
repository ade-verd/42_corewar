/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:47:47 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 11:44:36 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Handles Play/Pause
**
** @param env: Context structure
*/

static void		handle_space(t_env *env)
{
	if (env->gph->running == RUN)
		env->gph->running = PAUSE;
	else if (env->gph->running == PAUSE)
		env->gph->running = RUN;
	else if (env->gph->running == FW)
	{
		env->gph->running = PAUSE;
		env->goto_cycle = 0;
	}
	ft_wrefresh(env);
}

/*
** @brief: Handles "Goto" option which let us go directly to a specified cycle
**		   The specified cycle has to be bigger than the current cycle
**
** @param env: Context structure
*/

static void		handle_goto(t_env *env)
{
	int		c;

	c = 0;
	mvwprintw(env->gph->winf, 8, 2, "                                        ");
	wattron(env->gph->winf, A_BOLD);
	curs_set(2);
	mvwprintw(env->gph->winf, 8, 2, "Go to: int(5)     ");
	wscanw(env->gph->winf, "%5d", &c);
	curs_set(0);
	if (c <= env->cycle)
	{
		wattron(env->gph->winf, COLOR_PAIR(ERR_COLOR));
		mvwprintw(env->gph->winf, 8, 2, "ERROR: ");
		wattroff(env->gph->winf, COLOR_PAIR(ERR_COLOR));
		wprintw(env->gph->winf, "Must be an int bigger than %d", env->cycle);
		c = 0;
	}
	else
	{
		env->gph->running = FW;
		mvwprintw(env->gph->winf, 8, 2, "Please be patient... Going to %d", c);
	}
	wattroff(env->gph->winf, A_BOLD);
	ft_wrefresh(env);
	env->goto_cycle = c;
}

/*
** @brief: Handles refreshes and naps
**
** @param env: Context structure
*/

static void		actualize(t_env *env)
{
	int	nap;

	nap = 200 / env->gph->cycles_sec;
	if (env->cycle < env->goto_cycle)
	{
		if (env->cycle % 500 == 0)
			ft_wrefresh(env);
	}
	else if (env->cycle && env->cycle == env->goto_cycle)
	{
		wclear(env->gph->winf);
		visu_display_boxes(env->gph);
		env->goto_cycle = 0;
		env->gph->running = PAUSE;
		ft_wrefresh(env);
		visu_manage_events(env);
	}
	else
	{
		if (nap)
			napms(nap);
		ft_wrefresh(env);
	}
}

/*
** @brief: Checkes key pressed and does actions
**
** @param env: Context structure
** @param key: Key pressed
*/

void			visu_check_keys(t_env *env, int key)
{
	if (key == KEY_RESIZE)
		visu_resize(env);
	else if (key == ' ')
		handle_space(env);
	else if (key == '@')
		handle_goto(env);
	else if (key == KEY_LEFT && (env->gph->cycles_sec - 10) > 0)
		env->gph->cycles_sec -= 10;
	else if (key == KEY_RIGHT && (env->gph->cycles_sec + 10) <= 500)
		env->gph->cycles_sec += 10;
	else if (key == KEY_DOWN && (env->gph->cycles_sec - 1) > 0)
		env->gph->cycles_sec -= 1;
	else if (key == KEY_UP && (env->gph->cycles_sec + 1) <= 500)
		env->gph->cycles_sec += 1;
	else if (key == KEY_END)
		error(env, "NO", 0);
}

/*
** @brief: Handles actions on keyboard (events) with nCurses
**
** @param env: Context structure
*/

void			visu_manage_events(t_env *env)
{
	int			ky;

	if (!(env->flags & FLAG_NCURSES))
		return ;
	while (!env->goto_cycle && ((ky = ft_getch()) != ERR || !env->gph->running))
	{
		visu_check_keys(env, ky);
		ft_wrefresh(env);
	}
	actualize(env);
}
