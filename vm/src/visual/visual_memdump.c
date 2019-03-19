/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_memdump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:47:47 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/05 18:59:51 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Dumps memory on nCurses arena window
**
** @param env: Context structure
*/

void		visu_dump_arn(t_env *env)
{
	int		pc;
	int		diiv;

	if (!(env->flags & FLAG_NCURSES))
		return ;
	pc = 0;
	diiv = ft_sqrt(MEM_SIZE);
	werase(env->gph->warn);
	box(env->gph->warn, ACS_VLINE, ACS_HLINE);
	mvwprintw(env->gph->warn, 0, 2, " Arena ");
	while (pc < MEM_SIZE)
	{
		pc = pc % MEM_SIZE;
		if (env->color[pc])
		{
			wattron(env->gph->warn, COLOR_PAIR(env->color[pc]));
			mvwprintw(env->gph->warn, 1 + (pc / diiv), 1 + ((pc % diiv) * 3),
				"%02x", env->arena[pc]);
			wattroff(env->gph->warn, COLOR_PAIR(env->color[pc]));
		}
		pc++;
	}
}
