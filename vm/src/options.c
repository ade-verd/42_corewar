/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <oozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 09:46:25 by ade-verd          #+#    #+#             */
/*   Updated: 2019/03/13 10:50:01 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** @brief: Checks flags compatibility and adjust it
**
** @param env: Context structure
*/

void	options_compatibility(t_env *env)
{
	if (!env->flags)
		return ;
	if (env->flags & FLAG_PLAYER)
		env->flags &= ~FLAG_PLAYER;
	if (env->flags & FLAG_NCURSES)
	{
		if (env->flags & FLAG_DUMP)
			env->flags &= ~FLAG_DUMP;
		if (env->flags & FLAG_DUMPC)
			env->flags &= ~FLAG_DUMPC;
		if (env->flags & FLAG_SLEEP)
			env->flags &= ~FLAG_SLEEP;
	}
	if (env->flags & FLAG_SLEEP)
	{
		env->flags &= ~FLAG_DUMP;
		env->flags &= ~FLAG_DUMPC;
	}
	if (env->flags & FLAG_DUMP && env->flags & FLAG_DUMPC)
		env->flags &= ~FLAG_DUMP;
}

/*
** @brief: Handles flags DUMP | DUMPC | SLEEP
**
** @param env: Context structure
*/

void	deal_options_dump(t_env *env)
{
	if (env->flags & FLAG_SLEEP)
	{
		if (env->cycle % env->option_nb == 0 || env->cycle_to_die <= 0)
		{
			ft_printf("%7s Cycle %d\n", "", env->cycle);
			ft_dumpc_memory(env);
			getchar();
			return ;
		}
	}
	if (env->cycle == env->option_nb || env->cycle_to_die <= 0)
	{
		ft_printf("%7s Cycle %d\n", "", env->cycle);
		if (env->flags & FLAG_DUMP)
			ft_dump_memory(env);
		else if (env->flags & FLAG_DUMPC)
			ft_dumpc_memory(env);
		error(env, "NO", 0);
	}
}

/*
** @brief: Handles flags DUMP | DUMPC | NCURSES
**
** @param env: Context structure
*/

void	deal_options(t_env *env)
{
	if (!env->flags)
		return ;
	if (env->flags & (FLAG_DUMP | FLAG_DUMPC | FLAG_SLEEP) && env->option_nb)
		deal_options_dump(env);
	if (env->flags & FLAG_NCURSES)
	{
		if (env->gph)
			visu_manage_events(env);
		else if (env->cycle + 1 >= env->goto_cycle)
		{
			visu_init(env);
			visu_manage_events(env);
		}
	}
}
