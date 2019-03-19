/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_footer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:47:09 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 18:25:08 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Displays keys
**
** @param env: Context structure
** @param y: Ordinate
** @param tabx: Array of abscisses
*/

static void	visu_keys_legend(t_env *env, int y, int *tabx)
{
	int	i;
	int	d;

	i = 0;
	d = 2;
	mvwprintw(env->gph->wlgd, y, tabx[i], "Play / Pause");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Speed down -10");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Speed down -01");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Speed up  +01");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Speed up  +10");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Go to cycle ...");
	mvwprintw(env->gph->wlgd, y, tabx[i += d], "Exit");
	i = 0;
	wattron(env->gph->wlgd, A_STANDOUT);
	mvwprintw(env->gph->wlgd, y + 1, tabx[i], "  SPACEBAR  ");
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "      %C       ", 9664);
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "      %C       ", 9660);
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "      %C      ", 9650);
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "      %C      ", 9654);
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "       @       ");
	mvwprintw(env->gph->wlgd, y + 1, tabx[i += d], "END ");
	wattroff(env->gph->wlgd, A_STANDOUT);
}

/*
** @brief: Displays OP Legend
**
** @param env: Context structure
** @param y: Ordinate
** @param tabx: Array of abscisses
*/

static void	visu_op_legend(t_env *env, int y, int *tabx)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code != 404)
		{
			wattron(env->gph->wlgd, A_STANDOUT);
			mvwprintw(env->gph->wlgd, y, tabx[x], "%02X", g_op_tab[i].op_code);
			wattroff(env->gph->wlgd, A_STANDOUT);
			mvwprintw(env->gph->wlgd, y, tabx[x] + 3, "%s", g_op_tab[i].op);
			tabx[x + 1] = tabx[x] + 3 + ft_strlen(g_op_tab[i].op) + 6;
			x++;
		}
		i++;
	}
}

/*
** @brief: Displays legend
**
** @param env: Context structure
*/

void		visu_display_legend(t_env *env)
{
	int	y;
	int	tabx[20 + 1];

	y = 1;
	tabx[0] = 2;
	tabx[20] = 0;
	visu_op_legend(env, y, tabx);
	y += 2;
	visu_keys_legend(env, y, tabx);
}
