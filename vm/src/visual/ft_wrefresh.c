/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrefresh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <ade-verd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:37 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/20 18:28:55 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Main nCurses refresh function
**		   Dumps arena, Actualizes infos, and refreshes all windows
**
** @param env: Context structure
*/

void	ft_wrefresh(t_env *env)
{
	if (!(env->flags & FLAG_NCURSES) || !env->gph)
		return ;
	visu_dump_arn(env);
	visu_info(env, env->gph->winf);
	wrefresh(env->gph->warn);
	wrefresh(env->gph->winf);
	wrefresh(env->gph->wlgd);
	wrefresh(env->gph->wtrm);
}
