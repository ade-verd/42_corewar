/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_live_breakdown.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:59:32 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 19:08:03 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Gets the number of lives for the last or current period
**
** @param env: Context strucutre
** @param period: "Last" or current period
** @return int: Sum
*/

static int	get_sum_lives(t_env *env, char *period)
{
	t_player	*p;
	int			sum;

	sum = 0;
	p = env->player;
	while (p)
	{
		if (ft_strcmp(period, "last") == 0)
			sum += p->lives_last;
		else
			sum += p->lives_curr;
		p = p->next;
	}
	return (sum);
}

/*
** @brief: Displays default live breakdown
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
** @param visible:	0: Invisible spaces with A_NORMAL
**					1: Visible spaces with A_STANDOUT
*/

void		visu_default_bkdwn(t_env *env, int *y, int x, int visible)
{
	int			n;

	n = (env->gph->inf.c - 4);
	visible = visible == 0 ? A_NORMAL : A_STANDOUT;
	wattron(env->gph->winf, COLOR_BLACK | visible);
	while (n--)
		mvwprintw(env->gph->winf, *y, x++, " ");
	wattroff(env->gph->winf, COLOR_BLACK | visible);
}

/*
** @brief: Get's the color of the last player with at least one live
**
** @param env: Context structure
** @param id: Player id
** @param color: Int pointer of player's color
** @param prd: period "last" or current
*/

static void	color_adjust(t_env *env, unsigned int id, int *color, char *prd)
{
	t_player	*p;
	int			lives;

	p = env->player;
	lives = 0;
	while (p)
	{
		lives = !ft_strcmp(prd, "last") ? p->lives_last : p->lives_curr;
		if (lives > 0)
			*color = ft_abs(p->id);
		if (p->id == id)
			return ;
		p = p->next;
	}
}

/*
** @brief: Displays live breakdown for the current period
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
*/

void		visu_currlive_brkdown(t_env *env, int *y, int x)
{
	t_player	*p;
	int			sum;
	int			n;
	int			color;

	sum = env->nbr_live;
	p = env->player;
	mvwprintw(env->gph->winf, (*y)++, x, "Live breakdown for current period:");
	!sum ? visu_default_bkdwn(env, y, x, 1) : visu_default_bkdwn(env, y, x, 0);
	while (p && sum)
	{
		color = ft_abs(p->id);
		n = (p->lives_curr * (env->gph->inf.c - 4)) / sum;
		if (!p->next)
			n += (env->gph->inf.c - 2) - (x + n);
		color_adjust(env, p->id, &color, "curr");
		wattron(env->gph->winf, COLOR_PAIR(RCOLOR - color));
		while (n--)
			mvwprintw(env->gph->winf, *y, x++, " ");
		wattroff(env->gph->winf, COLOR_PAIR(RCOLOR - color));
		p = p->next;
	}
	(*y) += 2;
}

/*
** @brief: Displays live breakdown for the last period
**
** @param env: Context structure
** @param y: Ordinate
** @param x: Absciss
*/

void		visu_lastlive_brkdown(t_env *env, int *y, int x)
{
	t_player	*p;
	int			sum;
	int			n;
	int			color;

	sum = get_sum_lives(env, "last");
	p = env->player;
	mvwprintw(env->gph->winf, (*y)++, x, "Live breakdown for last period:");
	!sum ? visu_default_bkdwn(env, y, x, 1) : visu_default_bkdwn(env, y, x, 0);
	while (p && sum)
	{
		n = (p->lives_last * (env->gph->inf.c - 4)) / sum;
		if (!p->next)
			n += (env->gph->inf.c - 2) - (x + n);
		color_adjust(env, p->id, &color, "last");
		wattron(env->gph->winf, COLOR_PAIR(RCOLOR - color));
		while (n--)
			mvwprintw(env->gph->winf, *y, x++, " ");
		wattroff(env->gph->winf, COLOR_PAIR(RCOLOR - color));
		p = p->next;
	}
	(*y) += 2;
}
